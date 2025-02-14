#ifndef START_CREATE_LOADER_VIRTUAL_HOST_FROM_FILE_HPP
#define START_CREATE_LOADER_VIRTUAL_HOST_FROM_FILE_HPP

#include <fstream>
#include <string>

#include "../error/LogDefault.hpp"
#include "LoaderVirtualHost.hpp"

class LoaderVirtualHostFromFile : public LoaderVirtualHost {
 public:
  LoaderVirtualHostFromFile(const std::string &pathToFile);
  ~LoaderVirtualHostFromFile();
  LoaderVirtualHostFromFile(const LoaderVirtualHostFromFile &src);
  LoaderVirtualHostFromFile &operator=(const LoaderVirtualHostFromFile &src);

  error::StatusOr<std::vector<VirtualHostDefault *> > loadVirtualHosts();

 private:
  std::ifstream _file;
  std::string _pathToFile;

};

#endif