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

  std::string path = url.getPathFull(true);

  if (path.find(".php") != std::string::npos || path.find(".py") != std::string::npos) return true;

  return false;
}

std::string VirtualHostFake::getThePhysicalPath(const URL& url) const{

	std::string prefix = "www";

	if (isUrlAPathToCGI(url)){
		return prefix + url.getPath(true);
	}
	return prefix + url.getPathFull(true);
}

bool VirtualHostFake::isDirectoryListingAllowedForThisPath(const URL& url) const{
  std::string path = url.getPathFull(true);

  if (path.find("dir") != std::string::npos) return true;
  return false;
}

std::string VirtualHostFake::getThePathToCustomPageForHTTPStatus(HTTPStatus::Status httpStatus) const{
	(void)httpStatus;
	return "";
}

std::string VirtualHostFake::getRootDir(const URL& url) const{
	(void)url;
	return "www";
}

std::string VirtualHostFake::getIndexFile(const URL& url) const{
	std::string path = url.getPathFull(true);

	if (isUrlAPathToCGI(url)){
		path = url.getPath(true);
	}


	// just for demonstration purposes, if the URL is just the slash / we will
	// return a index.html file
	if (path == "/") return "index.php";
	if (path.find("dir_and_index_php") != std::string::npos) return "index.php";
	if (path.find("dir_and_index_html") != std::string::npos) return "index.html";
	return "";
}