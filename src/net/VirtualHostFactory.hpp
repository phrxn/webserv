#ifndef NET_VIRTUAL_HOST_FACTORY_HPP
#define NET_VIRTUAL_HOST_FACTORY_HPP

#include <map>
#include <string>

#include "../error/StatusOr.hpp"
#include "VirtualHost.hpp"
#include "VirtualHostCluster.hpp"

class VirtualHostFactory {
 public:
  static void fillTheFactory(const VirtualHostCluster &virtualHostCluster);
  static void destroyFactory();

  VirtualHostFactory();
  ~VirtualHostFactory();
  VirtualHostFactory(const VirtualHostFactory &src);
  VirtualHostFactory &operator=(const VirtualHostFactory &src);

  VirtualHost getVirtualHost(int port, const std::string &hostName) const;

 private:
  static VirtualHostCluster virtualHostCluster;
};

#endif