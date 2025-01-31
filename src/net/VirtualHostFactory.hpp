#ifndef NET_VIRTUAL_HOST_FACTORY_HPP
#define NET_VIRTUAL_HOST_FACTORY_HPP

#include <map>
#include <string>

#include "../error/Log.hpp"
#include "../error/StatusOr.hpp"
#include "VirtualHost.hpp"
#include "VirtualHostCluster.hpp"

class VirtualHostFactory {
 public:
  static void fillTheFactory(const VirtualHostCluster &virtualHostCluster);

  VirtualHostFactory();
  ~VirtualHostFactory();
  VirtualHostFactory(const VirtualHostFactory &src);
  VirtualHostFactory &operator=(const VirtualHostFactory &src);

  VirtualHost getVirtualHost(int port, const std::string &hostName) const;
  void setLogger(Log *logger);

 private:
  static VirtualHostCluster virtualHostCluster;
  Log *_logger;
};

#endif