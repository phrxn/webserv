#include "VirtualHostFactory.hpp"

#include <sstream>

#include "../Start.hpp"

VirtualHostCluster VirtualHostFactory::virtualHostCluster;

void VirtualHostFactory::fillTheFactory(
    const VirtualHostCluster &virtualHostCluster) {
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

VirtualHost VirtualHostFactory::getVirtualHost(
    int port, const std::string &hostName) const {
  error::StatusOr<VirtualHost> vh =
      virtualHostCluster.getVirtualHost(port, hostName);
  if (!vh.ok()) {
    if (_logger) {
      std::stringstream errorMessage;
      errorMessage << "port: " << port << ", hostname: " << hostName;

      _logger->log(Log::FATAL, "VirtualHostFactory", "getVirtualHost",
                   "using default VirtualHost, the virtualhost wasn't found",
                   errorMessage.str());
    }
    return VirtualHost(-1, "");
  }
  return vh.value();
}

void VirtualHostFactory::setLogger(Log *logger){
	_logger = logger;
}
