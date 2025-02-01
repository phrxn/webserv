#ifndef NET_VIRTUAL_HOST_CLUSTER_HPP
#define NET_VIRTUAL_HOST_CLUSTER_HPP

#include <list>
#include <map>

#include "../error/StatusOr.hpp"
#include "VirtualHostDefault.hpp"

class VirtualHostCluster {
 public:
  VirtualHostCluster();
  ~VirtualHostCluster();
  VirtualHostCluster(const VirtualHostCluster &src);
  VirtualHostCluster &operator=(const VirtualHostCluster &src);

  bool addVirtualHostToCluster(const VirtualHostDefault &VirtualHostDefault);
  virtual error::StatusOr<VirtualHostDefault> getVirtualHost(
      int port, const std::string &serverName) const;
  std::list<int> getAllPorts() const;

  const std::map<int, std::list<VirtualHostDefault> > &getMap() const;

 private:
  std::map<int, std::list<VirtualHostDefault> > _mapTheCluster;

};

#endif