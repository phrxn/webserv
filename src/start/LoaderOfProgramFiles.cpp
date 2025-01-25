#include "LoaderOfProgramFiles.hpp"

#include <list>

#include "../error/StatusOr.hpp"
#include "../net/VirtualHost.hpp"
#include "../net/http/MimeType.hpp"
#include "CreateMimeTypeMap.hpp"
#include "../net/VirtualHostFactory.hpp"

LoaderOfProgramFiles::LoaderOfProgramFiles(Log *logger) : _logger(logger) {}

LoaderOfProgramFiles::~LoaderOfProgramFiles() {}

LoaderOfProgramFiles::LoaderOfProgramFiles(const LoaderOfProgramFiles &src) {
  *this = src;
}

LoaderOfProgramFiles &LoaderOfProgramFiles::operator=(
    const LoaderOfProgramFiles &src) {
  if (this == &src) {
    return *this;
  }
  _logger = src._logger;
  return *this;
}

bool LoaderOfProgramFiles::loaderAllProgramThings(int argc, char **argv){
  (void)argv;
  if (!loadMimetypeListFromFile(_logger)) {
    return false;
  }

  if (!checkParameters(argc)) {
    return false;
  }

  if (!loadConfigurarionFile(argv)){
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

  MimeType::setMimetypeMap(mimeMap.value());

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

bool LoaderOfProgramFiles::loadConfigurarionFile(char **argv){

  std::list<VirtualHost> virtualHostsFromFile;
  VirtualHost a(8111, "abc");
  VirtualHost b(8110, "xyz");
  virtualHostsFromFile.push_back(a);
  virtualHostsFromFile.push_back(b);

  std::list<VirtualHost>::const_iterator it  = virtualHostsFromFile.begin();
  std::list<VirtualHost>::const_iterator end = virtualHostsFromFile.end();

  VirtualHostCluster virtualHostCluster;

  for (; it != end; ++it) {
    virtualHostCluster.addVirtualHostToCluster(*it);
  }

  VirtualHostFactory::fillTheFactory(virtualHostCluster);

  _allVirtualHostPorts = virtualHostCluster.getAllPorts();

  std::string pathToConfigurationFile = argv[1];

  return true;
}

void LoaderOfProgramFiles::setLogger(Log *logger) { _logger = logger; }

const std::list<int> &LoaderOfProgramFiles::getListOfAllVirtualHostPorts() const{
	return _allVirtualHostPorts;
}