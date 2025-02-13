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

  bool addVirtualHostToCluster(const VirtualHostDefault *VirtualHostFake);
  virtual error::StatusOr<const VirtualHostDefault*> getVirtualHost(unsigned int port, const std::string &serverName) const;
  std::list<int> getAllPorts() const;

  const std::map<int, std::list<const VirtualHostDefault*> > &getMap() const;

  void destroyAllVirtualHosts();

 private:
  std::map<int, std::list<const VirtualHostDefault*> > _mapTheCluster;

};

#endif