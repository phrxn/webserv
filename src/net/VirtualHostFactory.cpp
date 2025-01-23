#include "VirtualHostFactory.hpp"

#include <sstream>

#include "../Start.hpp"

VirtualHostCluster VirtualHostFactory::virtualHostCluster;

void VirtualHostFactory::fillTheFactory(const std::list<VirtualHost> &map) {
  std::list<VirtualHost>::const_iterator it;
  for (it = map.begin(); it != map.end(); ++it) {
    virtualHostCluster.addVirtualHostToCluster(*it);
  }
}

void VirtualHostFactory::destroyFactory() {}

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

VirtualHost VirtualHostFactory::getVirtualHost(
    int port, const std::string &hostName) const {
  error::StatusOr<VirtualHost> vh =
      virtualHostCluster.getVirtualHost(port, hostName);
  if (!vh.ok()) {
    if (Start::loggerGlobal) {
      std::stringstream errorMessage;
      errorMessage << "port: " << port << ", hostName: " << hostName;

      Start::loggerGlobal->log(
          Log::FATAL, "VirtualHostFactory", "getVirtualHost",
          "using default VirtualHost, the virtualhost wasn't found",
          errorMessage.str());
    }
	return VirtualHost(-1, "");
  }
  return vh.value();
}