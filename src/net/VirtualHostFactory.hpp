#ifndef NET_VIRTUAL_HOST_FACTORY_HPP
#define NET_VIRTUAL_HOST_FACTORY_HPP

#include <map>
#include <string>

#include "../error/StatusOr.hpp"
#include "VirtualHost.hpp"

class VirtualHostFactory {
 public:
  static void fillTheFactory(const std::map<std::string, const VirtualHost *> &map);
  static void destroyFactory();

  VirtualHostFactory();
  ~VirtualHostFactory();
  VirtualHostFactory(const VirtualHostFactory &src);
  VirtualHostFactory &operator=(const VirtualHostFactory &src);

  const VirtualHost *createVirtualHost(const std::string &hostName) const;

 private:
  static std::map<std::string, const VirtualHost *> mapOfVirtualHost;
};

#endif