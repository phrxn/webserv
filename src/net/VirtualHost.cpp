#include "VirtualHost.hpp"

VirtualHost::VirtualHost() {}

VirtualHost::VirtualHost(int port, const std::string &serverName)
    : _port(port), _serverName(serverName) {}

VirtualHost::~VirtualHost() {}

VirtualHost::VirtualHost(const VirtualHost &src) { *this = src; }

VirtualHost &VirtualHost::operator=(const VirtualHost &src) {
  if (this == &src) return *this;
  _port = src._port;
  _serverName = src._serverName;
  return *this;
}

bool VirtualHost::operator==(const VirtualHost &src) const {
  if (_port != src._port) return false;
  if (_serverName != src._serverName) return false;
  return true;
}

bool VirtualHost::isUrlAPathToCGI(std::string url) const {
  std::string::size_type phpExtesion = url.find(".php");
  return (phpExtesion != std::string::npos);
}

int VirtualHost::getPort() const { return _port; }

void VirtualHost::setPort(int port) { _port = port; }

std::string VirtualHost::getServername() const { return _serverName; }

void VirtualHost::setServername(const std::string &serverName) {
  _serverName = serverName;
}