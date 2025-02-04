#include "ClusterOfVirtualHost.hpp"

#include <algorithm>
#include <sstream>

ClusterOfVirtualHost::ClusterOfVirtualHost() {}

ClusterOfVirtualHost::~ClusterOfVirtualHost() {}

ClusterOfVirtualHost::ClusterOfVirtualHost(const ClusterOfVirtualHost &src) {
  *this = src;
}

ClusterOfVirtualHost &ClusterOfVirtualHost::operator=(
    const ClusterOfVirtualHost &src) {
  if (this == &src) return *this;
  _mapTheCluster = src._mapTheCluster;
  return *this;
}

bool ClusterOfVirtualHost::addVirtualHostToCluster(
    const VirtualHostDefault &virtualHost) {
  std::map<int, std::list<VirtualHostDefault> >::iterator itPortAndItsList =
      _mapTheCluster.find(virtualHost.getPort());

  // if the port doesn't have its list, let's create one
  if (itPortAndItsList == _mapTheCluster.end()) {
    std::list<VirtualHostDefault> listNewPort;
    listNewPort.push_back(virtualHost);
    _mapTheCluster[virtualHost.getPort()] = listNewPort;
    return true;
  }

  std::list<VirtualHostDefault> &list = itPortAndItsList->second;

  std::list<VirtualHostDefault>::iterator itVirtualHost =
      std::find(list.begin(), list.end(), virtualHost);

  // if the virtual host already exist in the list it cannot be inserted again
  if (itVirtualHost != list.end()) {
    return false;
  }

  list.push_back(virtualHost);
  return true;
}

error::StatusOr<VirtualHostDefault> ClusterOfVirtualHost::getVirtualHost(
    int port, const std::string &serverName) const {
  std::stringstream ss;

  std::map<int, std::list<VirtualHostDefault> >::const_iterator it =
      _mapTheCluster.find(port);

  if (it == _mapTheCluster.end()) {
    ss << "there is no host using port: " << port;
    return error::Status(error::Status::ObjectDoesnotExit, ss.str());
  }

  VirtualHostDefault toFind(port, serverName);

  const std::list<VirtualHostDefault> &listHostWithPortEquals = it->second;

  std::list<VirtualHostDefault>::const_iterator itList = std::find(
      listHostWithPortEquals.begin(), listHostWithPortEquals.end(), toFind);
  if (itList != listHostWithPortEquals.end()) {
    return *itList;
  }
  return *listHostWithPortEquals.begin();
}

std::list<int> ClusterOfVirtualHost::getAllPorts() const {
  std::list<int> allPorts;

  std::map<int, std::list<VirtualHostDefault> >::const_iterator it =
      _mapTheCluster.begin();
  std::map<int, std::list<VirtualHostDefault> >::const_iterator end =
      _mapTheCluster.end();

  for (; it != end; ++it) {
    allPorts.push_back(it->first);
  }
  return allPorts;
}

const std::map<int, std::list<VirtualHostDefault> > &ClusterOfVirtualHost::getMap()
    const {
  return _mapTheCluster;
}