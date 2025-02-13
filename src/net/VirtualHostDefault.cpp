#include "VirtualHostDefault.hpp"

VirtualHostDefault::VirtualHostDefault() {}

VirtualHostDefault::VirtualHostDefault(int port, const std::string &serverName)
    : _port(port), _serverName(serverName) {}

VirtualHostDefault::~VirtualHostDefault() {}

VirtualHostDefault::VirtualHostDefault(const VirtualHostDefault &src) { *this = src; }

VirtualHostDefault &VirtualHostDefault::operator=(const VirtualHostDefault &src) {
  if (this == &src) return *this;
  VirtualHost::operator=(src);
  _port = src._port;
  _serverName = src._serverName;
  return *this;
}

bool VirtualHostDefault::operator==(const VirtualHostDefault &src) const {
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

bool VirtualHostDefault::isPathValid(const URL& url)  const {
	(void)url;
	return true;
}

std::string VirtualHostDefault::isPathARedirection(const URL& url) const{
	(void)url;
	return "";
}

bool VirtualHostDefault::isTheMethodAllowedForThisPath(const URL& url, HTTPMethods::Method method) const{
		(void)url;
		(void)method;
	return true;
}

bool VirtualHostDefault::isUrlAPathToCGI(const URL& url) const{

  std::string path = url.getPathFull(false);

  if (path.find(".php") != std::string::npos || path.find(".py") != std::string::npos) return true;

  return false;
}

std::string VirtualHostDefault::getThePhysicalPath(const URL& url) const{
	std::string prefix = "www";
	return prefix + url.getPathFull(false);
}

bool VirtualHostDefault::isDirectoryListingAllowedForThisPath(const URL& url) const{
  std::string path = url.getPathFull(false);

  std::string::size_type phpExtesion = path.find("dir");

  return (phpExtesion != std::string::npos);
}

std::string VirtualHostDefault::getThePathToCustomPageForHTTPStatus(HTTPStatus::Status httpStatus) const{
	(void)httpStatus;
	return "";
}