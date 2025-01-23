#ifndef NET_VIRTUAL_HOST_CLUSTER_HPP
#define NET_VIRTUAL_HOST_CLUSTER_HPP

#include <list>
#include <map>

#include "../error/StatusOr.hpp"
#include "VirtualHost.hpp"

class VirtualHostCluster {
 public:
  VirtualHostCluster();
  ~VirtualHostCluster();
  VirtualHostCluster(const VirtualHostCluster &src);
  VirtualHostCluster &operator=(const VirtualHostCluster &src);

  bool addVirtualHostToCluster(const VirtualHost &VirtualHost);
  error::StatusOr<VirtualHost> getVirtualHost(
      int port, const std::string &serverName) const;

  const std::map<int, std::list<VirtualHost> > &getMap() const;

 private:
  std::map<int, std::list<VirtualHost> > _mapTheCluster;

};

#endif