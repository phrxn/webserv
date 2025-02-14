#include "VirtualHostFake.hpp"

VirtualHostFake::VirtualHostFake() {}

VirtualHostFake::VirtualHostFake(int port, const std::string &serverName)
    : VirtualHostDefault(port, serverName) {}

VirtualHostFake::~VirtualHostFake() {}

VirtualHostFake::VirtualHostFake(const VirtualHostFake &src) { *this = src; }

VirtualHostFake &VirtualHostFake::operator=(const VirtualHostFake &src) {
  if (this == &src) return *this;
  _port = src._port;
  _serverName = src._serverName;
  return *this;
}

bool VirtualHostFake::isPathValid(const URL& url)  const {
	(void)url;
	return true;
}

std::string VirtualHostFake::isPathARedirection(const URL& url) const{
	(void)url;
	return "";
}

bool VirtualHostFake::isTheMethodAllowedForThisPath(const URL& url, HTTPMethods::Method method) const{
		(void)url;
		(void)method;
	return true;
}

bool VirtualHostFake::isUrlAPathToCGI(const URL& url) const{

  std::string path = url.getPathFull(false);

  if (path.find(".php") != std::string::npos || path.find(".py") != std::string::npos) return true;

  return false;
}

std::string VirtualHostFake::getThePhysicalPath(const URL& url) const{

	std::string prefix = "www";

	if (isUrlAPathToCGI(url)){
		return prefix + url.getPath(true);
	}
	return prefix + url.getPathFull(false);
}

bool VirtualHostFake::isDirectoryListingAllowedForThisPath(const URL& url) const{
  std::string path = url.getPathFull(false);

  std::string::size_type phpExtesion = path.find("dir");

  return (phpExtesion != std::string::npos);
}

std::string VirtualHostFake::getThePathToCustomPageForHTTPStatus(HTTPStatus::Status httpStatus) const{
	(void)httpStatus;
	return "";
}

std::string VirtualHostFake::getRootDir(const URL& url) const{
	(void)url;
	return "www";
}