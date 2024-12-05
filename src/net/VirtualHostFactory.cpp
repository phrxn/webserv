#include "VirtualHostFactory.hpp"

std::map<std::string, const VirtualHost *> VirtualHostFactory::mapOfVirtualHost;

void VirtualHostFactory::fillTheFactory(const
    std::map<std::string, const VirtualHost *> &map) {

	std::map<std::string, const VirtualHost *>::const_iterator it;
	for (it = map.begin(); it != map.end(); ++it){
		mapOfVirtualHost[it->first] = it->second;
	}
}

void VirtualHostFactory::destroyFactory() {

	std::map<std::string, const VirtualHost *>::iterator it;
	for (it = mapOfVirtualHost.begin(); it != mapOfVirtualHost.end(); ++it){
		delete it->second;
	}
}

VirtualHostFactory::VirtualHostFactory() {}

VirtualHostFactory::~VirtualHostFactory() {}

VirtualHostFactory::VirtualHostFactory(const VirtualHostFactory &src) {
  *this = src;
}

VirtualHostFactory &VirtualHostFactory::operator=(
    const VirtualHostFactory &src) {
  (void)src;
  return *this;
}

const VirtualHost *VirtualHostFactory::createVirtualHost(
    const std::string &hostName) const {
  if (mapOfVirtualHost.find(hostName) != mapOfVirtualHost.end())
    return mapOfVirtualHost[hostName];
  return NULL;
}