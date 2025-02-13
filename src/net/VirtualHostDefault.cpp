#include "VirtualHostDefault.hpp"

VirtualHostDefault::VirtualHostDefault() {}

VirtualHostDefault::VirtualHostDefault(int port) : _port(port) {}

VirtualHostDefault::VirtualHostDefault(int port, const std::string &serverName)
    : _port(port), _serverName(serverName) {}

VirtualHostDefault::~VirtualHostDefault() {}

VirtualHostDefault::VirtualHostDefault(const VirtualHostDefault &src) : _port(src._port), _serverName(src._serverName) {
	(void)src;
}

VirtualHostDefault &VirtualHostDefault::operator=(
    const VirtualHostDefault &src) {
  if (this == &src) return *this;
  _port = src._port;
  _serverName = src._serverName;
  return *this;
}

bool VirtualHostDefault::operator==(const VirtualHostDefault &src) const {
  if (this == &src) return true;
  if (_port != src._port) return false;
  if (_serverName != src._serverName) return false;
  return true;
}

unsigned int VirtualHostDefault::getPort() const { return _port; }

void VirtualHostDefault::setPort(unsigned int port) { _port = port; }

std::string VirtualHostDefault::getServerName() const { return _serverName; }

void VirtualHostDefault::setServerName(const std::string &serverName) {
  _serverName = serverName;
}