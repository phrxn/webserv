#ifndef NET_CLUSTER_OF_VIRTUAL_HOST_HPP
#define NET_CLUSTER_OF_VIRTUAL_HOST_HPP

#include <list>
#include <map>

#include "../error/StatusOr.hpp"
#include "VirtualHostDefault.hpp"

class ClusterOfVirtualHost {
 public:
  ClusterOfVirtualHost();
  ~ClusterOfVirtualHost();
  ClusterOfVirtualHost(const ClusterOfVirtualHost &src);
  ClusterOfVirtualHost &operator=(const ClusterOfVirtualHost &src);

  bool addVirtualHostToCluster(const VirtualHostDefault &VirtualHostDefault);
  virtual error::StatusOr<VirtualHostDefault> getVirtualHost(
      int port, const std::string &serverName) const;
  std::list<int> getAllPorts() const;

  const std::map<int, std::list<VirtualHostDefault> > &getMap() const;

 private:
  std::map<int, std::list<VirtualHostDefault> > _mapTheCluster;

};

#endif