#include "VirtualHostFactory.hpp"

#include <sstream>

#include "../Start.hpp"

ClusterOfVirtualHost VirtualHostFactory::virtualHostCluster;

void VirtualHostFactory::fillTheFactory(
    const ClusterOfVirtualHost &virtualHostCluster) {
  VirtualHostFactory::virtualHostCluster = virtualHostCluster;
}

VirtualHostFactory::VirtualHostFactory() : _logger(LogDefault::loggerGlobal) {}

VirtualHostFactory::~VirtualHostFactory() {}

VirtualHostFactory::VirtualHostFactory(const VirtualHostFactory &src) {
  *this = src;
}

VirtualHostFactory &VirtualHostFactory::operator=(
    const VirtualHostFactory &src) {
  if (this == &src) return *this;
  _logger = src._logger;
  return *this;
}

VirtualHostDefault VirtualHostFactory::getVirtualHost(
    int port, const std::string &hostName) const {
  error::StatusOr<VirtualHostDefault> vh =
      virtualHostCluster.getVirtualHost(port, hostName);
  if (!vh.ok()) {
    if (_logger) {
      std::stringstream errorMessage;
      errorMessage << "port: " << port << ", hostname: " << hostName;

      _logger->log(Log::FATAL, "VirtualHostFactory", "getVirtualHost",
                   "using default VirtualHostDefault, the virtualhost wasn't found",
                   errorMessage.str());
    }
    return getDefaultVirtualHost();
  }
  return vh.value();
}

VirtualHostDefault VirtualHostFactory::getDefaultVirtualHost() const{
  return VirtualHostDefault(-1, "");
}

void VirtualHostFactory::setLogger(Log *logger){
	_logger = logger;
}
