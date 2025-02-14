#include "LoaderVirtualHostFromFile.hpp"

#include "../file_configuration/Config.hpp"

LoaderVirtualHostFromFile::LoaderVirtualHostFromFile(
    const std::string &pathToFile)
    : _pathToFile(pathToFile) {}

LoaderVirtualHostFromFile::~LoaderVirtualHostFromFile() {}

LoaderVirtualHostFromFile::LoaderVirtualHostFromFile(
    const LoaderVirtualHostFromFile &src)
    : _pathToFile(src._pathToFile) {
  (void)src;
}

LoaderVirtualHostFromFile &LoaderVirtualHostFromFile::operator=(
    const LoaderVirtualHostFromFile &src) {
  if (this == &src) {
    return *this;
  }
  _pathToFile = src._pathToFile;
  return *this;
}

// Return an array of Virtual Hosts from a file
//
// the list will be empty if there was an error or there are no virtual hosts in
// the file
error::StatusOr<std::vector<VirtualHostDefault *> > LoaderVirtualHostFromFile::loadVirtualHosts(){
  std::vector<VirtualHostDefault *> vectorOfVirtualHosts;

  try {
    Config config(_pathToFile);

    std::vector<ServerConfig> serverConfigs = config.getServers();

	std::vector<ServerConfig>::const_iterator it = serverConfigs.begin();

    for (; it != serverConfigs.end(); ++it) {
      ServerConfig *virtualHost = new ServerConfig(*it);
      vectorOfVirtualHosts.push_back(virtualHost);
    }
  } catch (std::exception &e) {
	return error::Status(error::Status::FileOpen, e.what());
  }

  return vectorOfVirtualHosts;
}
