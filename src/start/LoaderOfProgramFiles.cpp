#include "LoaderOfProgramFiles.hpp"

#include <list>

#include "../error/StatusOr.hpp"
#include "../net/VirtualHostDefault.hpp"
#include "../net/VirtualHostFactory.hpp"
#include "../net/VirtualHostFake.hpp"
#include "../net/http/GetMimeType.hpp"
#include "CreateDefaultErrorPages.hpp"
#include "CreateDefaultErrorPagesFactory.hpp"
#include "CreateMimeTypeMap.hpp"

LoaderOfProgramFiles::LoaderOfProgramFiles(Log *logger) : _logger(logger),
   _programConfiguration(ProgramConfiguration::getInstance()) {}

LoaderOfProgramFiles::LoaderOfProgramFiles(Log *logger, const ProgramConfiguration &programConfiguration) :
   _logger(logger), _programConfiguration(programConfiguration) {}

LoaderOfProgramFiles::~LoaderOfProgramFiles() {}

LoaderOfProgramFiles::LoaderOfProgramFiles(const LoaderOfProgramFiles &src) :
_logger(src._logger), _programConfiguration(src._programConfiguration) {
  *this = src;
}

LoaderOfProgramFiles &LoaderOfProgramFiles::operator=(
    const LoaderOfProgramFiles &src) {
  if (this == &src) {
    return *this;
  }
  _logger = src._logger;
  _allVirtualHostPorts = src._allVirtualHostPorts;
  return *this;
}

bool LoaderOfProgramFiles::loaderAllProgramThings(int argc, char **argv) {
  if (!loadMimetypeListFromFile(_logger)) {
    return false;
  }

  if (!loadDefaultErrorPages(_logger)) {
    return false;
  }

  if (!checkParameters(argc)) {
    return false;
  }

  if (!loadConfigurarionFile(argv)) {
    return false;
  }

  return true;
}

bool LoaderOfProgramFiles::loadMimetypeListFromFile(Log *logger) const {
  CreateMimeTypeMap createMimetypeMap;

  error::StatusOr<std::map<std::string, std::string> > mimeMap =
      createMimetypeMap.loadMimetypeMap("conf/mime.types");

  if (!mimeMap.ok()) {
    logger->log(Log::FATAL, "LoaderOfProgramFiles", "loadMimetypeListFromFile",
                "create the mimeType map", mimeMap.status().message());
    return false;
  }

  GetMimeType::setMimetypeMap(mimeMap.value());

  return true;
}

bool LoaderOfProgramFiles::loadDefaultErrorPages(Log *logger) const {
  CreateDefaultErrorPages createDefaultErrorPages;

  error::StatusOr<std::map<HTTPStatus::Status, ErrorPageFileHTMLDocument *> >
      allDefaultErrorPages = createDefaultErrorPages.loadDefaultPageErrorsMap();

  if (!allDefaultErrorPages.ok()) {
    logger->log(Log::FATAL, "LoaderOfProgramFiles", "loadDefaultErrorPages",
                "Unable to load all server error pages",
                allDefaultErrorPages.status().message());
    return false;
  }

  CreateDefaultErrorPagesFactory::fillTheFactory(allDefaultErrorPages.value());

  return true;
}

bool LoaderOfProgramFiles::checkParameters(int argc) const {
  if (argc < 2) {
    _logger->log(Log::FATAL, "LoaderOfProgramFiles", "checkParameters",
                 "invalid parameters", "please provide a configuration file");
    return false;
  }
  if (argc > 2) {
    _logger->log(
        Log::FATAL, "LoaderOfProgramFiles", "checkParameters",
        "invalid parameters",
        "the only parameter accepted by the program is the configuration file");
    return false;
  }
  return true;
}

bool LoaderOfProgramFiles::loadConfigurarionFile(char **argv) {

  std::vector<VirtualHostDefault *> virtualHostsFromFile;

  LoaderVirtualHost *loaderVirtualHost = NULL;

  if (_programConfiguration.getCreateVirtualHostsFromConfigurationFile()) {
	loaderVirtualHost = new LoaderVirtualHostFromFile(std::string(argv[1]));
  } else {
	loaderVirtualHost = new LoaderVirtualHostFake();
  }

  error::StatusOr<std::vector<VirtualHostDefault *> > virtualHosts = loaderVirtualHost->loadVirtualHosts();

  if (virtualHosts.ok()) {
	virtualHostsFromFile = virtualHosts.value();
  }
  delete loaderVirtualHost;
  if (!virtualHosts.ok()){
	_logger->log(Log::FATAL, "LoaderOfProgramFiles", "loadConfigurarionFile", virtualHosts.status().message(), "");
	return false;
  }
  if (virtualHostsFromFile.empty()) {
	_logger->log(Log::FATAL, "LoaderOfProgramFiles", "loadConfigurarionFile", "No configured server found!", "");
	return false;
  }

  std::vector<VirtualHostDefault *>::const_iterator it = virtualHostsFromFile.begin();
  std::vector<VirtualHostDefault *>::const_iterator end = virtualHostsFromFile.end();

  ClusterOfVirtualHost virtualHostCluster;

  for (; it != end; ++it) {
    if (!virtualHostCluster.addVirtualHostToCluster(*it)){
		delete *it;
	}
  }

  VirtualHostFactory::fillTheFactory(virtualHostCluster);

  _allVirtualHostPorts = virtualHostCluster.getAllPorts();

  std::string pathToConfigurationFile = argv[1];

  return true;
}

void LoaderOfProgramFiles::setLogger(Log *logger) { _logger = logger; }

const std::list<int> &LoaderOfProgramFiles::getListOfAllVirtualHostPorts()
    const {
  return _allVirtualHostPorts;
}