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

bool ClusterOfVirtualHost::addVirtualHostToCluster(const VirtualHostDefault *virtualHost) {

  std::map<int, std::list<const VirtualHostDefault*> >::iterator itPortAndItsList = _mapTheCluster.find(virtualHost->getPort());

  // if the port doesn't have its list, let's create one
  if (itPortAndItsList == _mapTheCluster.end()) {
    std::list<const VirtualHostDefault*> listNewPort;
    listNewPort.push_back(virtualHost);
    _mapTheCluster[virtualHost->getPort()] = listNewPort;
    return true;
  }

  std::list<const VirtualHostDefault*> &list = itPortAndItsList->second;

  std::list<const VirtualHostDefault*>::const_iterator itVirtualHost = list.begin();
  std::list<const VirtualHostDefault*>::const_iterator endVirtualHost = list.end();

  for(; itVirtualHost != endVirtualHost; ++itVirtualHost){
	if ((*itVirtualHost)->getServerName() == virtualHost->getServerName() &&
		(*itVirtualHost)->getPort() == virtualHost->getPort()) {
	  return false;
    }
  }

  list.push_back(virtualHost);
  return true;
}

error::StatusOr<const VirtualHostDefault*> ClusterOfVirtualHost::getVirtualHost(
    unsigned int port, const std::string &serverName) const {
  std::stringstream ss;

  std::map<int, std::list<const VirtualHostDefault *> >::const_iterator it = _mapTheCluster.find(port);

  if (it == _mapTheCluster.end()) {
    ss << "there is no host using port: " << port;
    return error::Status(error::Status::ObjectDoesnotExit, ss.str());
  }

  const std::list<const VirtualHostDefault*> &listHostWithPortEquals = it->second;

  std::list<const VirtualHostDefault*>::const_iterator itVirtualHostsOnThisPort = listHostWithPortEquals.begin();

  for(; itVirtualHostsOnThisPort != listHostWithPortEquals.end(); ++itVirtualHostsOnThisPort){
	if (((*itVirtualHostsOnThisPort)->getServerName() == serverName) &&
		((*itVirtualHostsOnThisPort)->getPort() == port)) {
	  return *itVirtualHostsOnThisPort;
	}
  }

  return *listHostWithPortEquals.begin();
}

std::list<int> ClusterOfVirtualHost::getAllPorts() const {
  std::list<int> allPorts;

  std::map<int, std::list<const VirtualHostDefault*> >::const_iterator it = _mapTheCluster.begin();
  std::map<int, std::list<const VirtualHostDefault*> >::const_iterator end = _mapTheCluster.end();

  for (; it != end; ++it) {
    allPorts.push_back(it->first);
  }
  return allPorts;
}

const std::map<int, std::list<const VirtualHostDefault*> > &ClusterOfVirtualHost::getMap()
    const {
  return _mapTheCluster;
}

void ClusterOfVirtualHost::destroyAllVirtualHosts(){

	std::map<int, std::list<const VirtualHostDefault*> >::iterator itListOfVirtualHost = _mapTheCluster.begin();
	std::map<int, std::list<const VirtualHostDefault*> >::iterator endListOfVirtualHost = _mapTheCluster.end();

	for(; itListOfVirtualHost != endListOfVirtualHost; ++itListOfVirtualHost){

		std::list<const VirtualHostDefault*> &list = itListOfVirtualHost->second;

		std::list<const VirtualHostDefault*>::iterator itVirtualHost = list.begin();
		std::list<const VirtualHostDefault*>::iterator endVirtualHost = list.end();

		for(; itVirtualHost != endVirtualHost; ++itVirtualHost){
			delete *itVirtualHost;
		}
	}
}