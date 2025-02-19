#include "CGICreateEnvironmentVariables.hpp"

#include <algorithm>
#include <sstream>

CGICreateEnvironmentVariables::CGICreateEnvironmentVariables(
    const std::string &physicalPathToResource,
    const std::string &rootVirtualHostLocation)
    : _physicalPathToResource(physicalPathToResource),
      _rootVirtualHostLocation(rootVirtualHostLocation),
      _configuration(ProgramConfiguration::getInstance()) {}

CGICreateEnvironmentVariables::~CGICreateEnvironmentVariables() {}

CGICreateEnvironmentVariables::CGICreateEnvironmentVariables(
    const CGICreateEnvironmentVariables &src) {
  *this = src;
}

CGICreateEnvironmentVariables &CGICreateEnvironmentVariables::operator=(
    const CGICreateEnvironmentVariables &src) {
  if (this == &src) {
    return *this;
  }

  _physicalPathToResource = src._physicalPathToResource;
  _rootVirtualHostLocation = src._rootVirtualHostLocation;
  _configuration = src._configuration;
  _httpMethods = src._httpMethods;
  _mapVariables = src._mapVariables;

  return *this;
}

bool CGICreateEnvironmentVariables::operator==(const CGICreateEnvironmentVariables &src) const{
  if (this == &src) {return true;}
  if (_physicalPathToResource != src._physicalPathToResource) {return false;}
  if (_rootVirtualHostLocation != src._rootVirtualHostLocation) {return false;}
  if (_mapVariables != src._mapVariables) {return false;}
  return true;
}

std::map<std::string, std::string>
CGICreateEnvironmentVariables::createCGIVariables(HTTPRequest *hTTPRequest) {

  _mapVariables["AUTH_TYPE"] = "";
  _mapVariables["CONTENT_LENGTH"] = hTTPRequest->getContentLength();
  _mapVariables["CONTENT_TYPE"] = hTTPRequest->getContentType();
  _mapVariables["GATEWAY_INTERFACE"] = _configuration.getCGIVersion();

  std::string extraPath = hTTPRequest->getURL().getExtraPathFromFullPath(false);
  if (extraPath != "") {
    std::string extraPathDecoded =
        hTTPRequest->getURL().getExtraPathFromFullPath(true);
    _mapVariables["PATH_INFO"] = extraPathDecoded;
	if (!_rootVirtualHostLocation.empty() && _rootVirtualHostLocation[_rootVirtualHostLocation.length() - 1] == '/') {
        _rootVirtualHostLocation.erase(_rootVirtualHostLocation.length() - 1);
    }
    _mapVariables["PATH_TRANSLATED"] =
        _rootVirtualHostLocation + extraPathDecoded;
  }

  _mapVariables["QUERY_STRING"] = hTTPRequest->getURL().getQuery();
  _mapVariables["REMOTE_ADDR"] = hTTPRequest->getClientAddressIPv4();
  _mapVariables["REMOTE_HOST"] = "";
  _mapVariables["REMOTE_IDENT"] = "";
  _mapVariables["REMOTE_USER"] = "";
  _mapVariables["REQUEST_METHOD"] =
      _httpMethods.getMethodToString(hTTPRequest->getMethod());
  _mapVariables["SCRIPT_NAME"] = hTTPRequest->getURL().getPath(true);
  _mapVariables["SERVER_NAME"] = hTTPRequest->getHost();
  _mapVariables["SERVER_PORT"] = getServerPort(hTTPRequest->getPort());
  _mapVariables["SERVER_PROTOCOL"] = _configuration.getHTTPVersion();
  _mapVariables["SERVER_SOFTWARE"] = _configuration.getServerName();
  _mapVariables["REDIRECT_STATUS"] = "true";
  _mapVariables["SCRIPT_FILENAME"] = _physicalPathToResource;

  if (!hTTPRequest->getCookie().empty()) {
    _mapVariables["HTTP_COOKIE"] = hTTPRequest->getCookie();
  }

  return _mapVariables;
}

std::string CGICreateEnvironmentVariables::getServerPort(int serverPort) const {
  std::stringstream ss;
  ss << serverPort;

  return ss.str();
}

void CGICreateEnvironmentVariables::setProgramConfiguration(
    const ProgramConfiguration &configuration) {
  _configuration = configuration;
}

std::string CGICreateEnvironmentVariables::getPhysicalPathToResource() const {
	return _physicalPathToResource;
}

std::string CGICreateEnvironmentVariables::getRootVirtualHostLocation() const {
	return _rootVirtualHostLocation;
}

std::ostream &operator<<(std::ostream &os,
						 const std::map<std::string, std::string> &mapVariables) {
  os << "CGICreateEnvironmentVariables: {\n";

  std::map<std::string, std::string>::const_iterator it = mapVariables.begin();
  std::map<std::string, std::string>::const_iterator end = mapVariables.end();

  for(; it != end; ++it) {
	os << "\t" << it->first << ": " << it->second << "\n";
  }
  os << " }\n";
  return os;
}