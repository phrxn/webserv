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

int VirtualHostDefault::getPort() const { return _port; }

void VirtualHostDefault::setPort(int port) { _port = port; }

std::string VirtualHostDefault::getServername() const { return _serverName; }

void VirtualHostDefault::setServername(const std::string &serverName) {
  _serverName = serverName;
}

bool VirtualHostDefault::isPathValid(URL url) const {
	(void)url;
	return true;
}

std::string VirtualHostDefault::isPathARedirection(URL url) const{
	(void)url;
	return "";
}

bool VirtualHostDefault::isTheMethodAllowedForThisPath(URL url, HTTPMethods::Method method) const{
		(void)url;
		(void)method;
	return true;
}

bool VirtualHostDefault::isUrlAPathToCGI(URL url) const{

  std::string path = url.getPathFull(false);

  if (path.find(".php") != std::string::npos || path.find(".py") != std::string::npos) return true;

  return false;
}

std::string VirtualHostDefault::getThePhysicalPath(URL url) const{
	std::string prefix = "www";
	return prefix + url.getPathFull(false);
}

bool VirtualHostDefault::isDirectoryListingAllowedForThisPath(URL url) const{
  std::string path = url.getPathFull(false);

  std::string::size_type phpExtesion = path.find("dir");

  return (phpExtesion != std::string::npos);
}

std::string VirtualHostDefault::getThePathToCustomPageForHTTPStatus(HTTPStatus::Status httpStatus) const{
	(void)httpStatus;
	return "";
}