#include "VirtualHostCluster.hpp"

#include <algorithm>
#include <sstream>

VirtualHostCluster::VirtualHostCluster() {}

VirtualHostCluster::~VirtualHostCluster() {}

VirtualHostCluster::VirtualHostCluster(const VirtualHostCluster &src) {
	*this = src;
}

VirtualHostCluster &VirtualHostCluster::operator=(
    const VirtualHostCluster &src) {
	if (this == &src) return *this;
	_mapTheCluster = src._mapTheCluster;
	return *this;
}

bool VirtualHostCluster::addVirtualHostToCluster(
    const VirtualHost &virtualHost) {
  std::map<int, std::list<VirtualHost> >::iterator itPortAndItsList =
      _mapTheCluster.find(virtualHost.getPort());

  // if the port doesn't have its list, let's create one
  if (itPortAndItsList == _mapTheCluster.end()) {
    std::list<VirtualHost> listNewPort;
    listNewPort.push_back(virtualHost);
    _mapTheCluster[virtualHost.getPort()] = listNewPort;
    return true;
  }

  std::list<VirtualHost> &list = itPortAndItsList->second;

  std::list<VirtualHost>::iterator itVirtualHost =
      std::find(list.begin(), list.end(), virtualHost);

  // if the virtual host already exist in the list it cannot be inserted again
  if (itVirtualHost != list.end()) {
    return false;
  }

  list.push_back(virtualHost);
  return true;
}

error::StatusOr<VirtualHost> VirtualHostCluster::getVirtualHost(
    int port, const std::string &serverName) const {

	std::stringstream ss;

    std::map<int, std::list<VirtualHost> >::const_iterator it =	_mapTheCluster.find(port);

	if (it == _mapTheCluster.end()){
		ss << "there is no host using port: " << port;
		return error::Status(error::Status::ObjectDoesnotExit, ss.str());
	}

	VirtualHost toFind(port, serverName);

	const std::list<VirtualHost> &listHostWithPortEquals = it->second;

	std::list<VirtualHost>::const_iterator itList = std::find(listHostWithPortEquals.begin(), listHostWithPortEquals.end(), toFind);
	if (itList != listHostWithPortEquals.end()){
		return *itList;
	}
	return *listHostWithPortEquals.begin();
}

const std::map<int, std::list<VirtualHost> > & VirtualHostCluster::getMap() const{
	return _mapTheCluster;
}