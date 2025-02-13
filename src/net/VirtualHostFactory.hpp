#ifndef NET_VIRTUAL_HOST_FACTORY_HPP
#define NET_VIRTUAL_HOST_FACTORY_HPP

#include <map>
#include <string>

#include "../error/Log.hpp"
#include "../error/StatusOr.hpp"
#include "VirtualHostDefault.hpp"
#include "ClusterOfVirtualHost.hpp"

class VirtualHostFactory {
 public:
  static void fillTheFactory(const ClusterOfVirtualHost &virtualHostCluster);
  static void destroyFactory();

  VirtualHostFactory();
  ~VirtualHostFactory();
  VirtualHostFactory(const VirtualHostFactory &src);
  VirtualHostFactory &operator=(const VirtualHostFactory &src);

  const VirtualHostDefault *getVirtualHost(int port, const std::string &hostName) const;
  void setLogger(Log *logger);

 private:
  static ClusterOfVirtualHost virtualHostCluster;
  Log *_logger;
};

#endif