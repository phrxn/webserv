#include "CGICreateEnvironmentVariables.hpp"

#include <algorithm>
#include <sstream>

#include "../../../config/Configuration.hpp"

CGICreateEnvironmentVariables::CGICreateEnvironmentVariables()
    : _configuration(Configuration::getInstance()) {}

CGICreateEnvironmentVariables::~CGICreateEnvironmentVariables() {}

// deleted (this class MUST BE UNIQUE!)
CGICreateEnvironmentVariables::CGICreateEnvironmentVariables(
    const CGICreateEnvironmentVariables &src)
    : _configuration(src._configuration) {
  (void)src;
}

// deleted (this class MUST BE UNIQUE!)
CGICreateEnvironmentVariables &CGICreateEnvironmentVariables::operator=(
    CGICreateEnvironmentVariables &src) {
  (void)src;
  return *this;
}

std::map<std::string, std::string>
CGICreateEnvironmentVariables::createCGIVariables(
    const SocketFileDescriptor *_socketFD, const VirtualHost *_virtualHost,
    const HTTPRequest *_hTTPRequest, const Configuration &_configuration) {
  (void)_socketFD;
  (void)_virtualHost;
  (void)_hTTPRequest;
  (void)_configuration;

  URL decoder;
  std::map<std::string, std::string> mapVariables;

  mapVariables["AUTH_TYPE"] = "";
  mapVariables["CONTENT_LENGTH"] = _hTTPRequest->getContentLength();
  mapVariables["CONTENT_TYPE"] = _hTTPRequest->getContentType();
  mapVariables["GATEWAY_INTERFACE"] = "CGI/1.1";

  std::string extraPath = extractExtraPath(_hTTPRequest->getURL(),
                                           _virtualHost->getScriptExtension());
  if (extraPath != "") {
    std::string extraPathDecoded = decoder.decode(extraPath);
    mapVariables["PATH_INFO"] = extraPathDecoded;
    mapVariables["PATH_TRANSLATED"] =
        extraPathDecoded + _virtualHost->getRootFolder();
  }
  mapVariables["QUERY_STRING"] = _hTTPRequest->getURL().getQuery();
  mapVariables["REMOTE_ADDR"] = _socketFD->getClientIPv4();
  mapVariables["REMOTE_HOST"] = "";
  mapVariables["REMOTE_IDENT"] = "";
  mapVariables["REMOTE_USER"] = "";
  mapVariables["REQUEST_METHOD"] = methodToString(_hTTPRequest->getMethod());
  mapVariables["SCRIPT_NAME"] =
      decoder.decode(_hTTPRequest->getURL().getPath());
  mapVariables["SERVER_NAME"] = _hTTPRequest->getHost();
  mapVariables["SERVER_PORT"] = getServerPort(_socketFD->getServerPort());
  mapVariables["SERVER_PROTOCOL"] = "HTTP/1.1";
  mapVariables["SERVER_SOFTWARE"] =
      Configuration::getInstance().getWebserverName();
  return mapVariables;
}

std::string CGICreateEnvironmentVariables::extractScriptPath(
    const URL &url, const std::string &scriptExtesion) const {
  std::string path = url.getPath();

  std::string::size_type delimiter = path.find(scriptExtesion);
  if (delimiter == std::string::npos) return path;
  return path.substr(0, delimiter + scriptExtesion.length());
}

std::string CGICreateEnvironmentVariables::extractExtraPath(
    const URL &url, const std::string &scriptExtesion) const {
  std::string pathToScript = extractScriptPath(url, scriptExtesion);

  return url.getPath().substr(pathToScript.length());
}

std::string CGICreateEnvironmentVariables::getServerPort(int serverPort) const {
  std::stringstream ss;
  ss << serverPort;

  return ss.str();
}

std::string CGICreateEnvironmentVariables::methodToString(
    HTTPMethods::Method method) const {
  if (method == HTTPMethods::GET) switch (method) {
      case HTTPMethods::GET:
        return "GET";
      case HTTPMethods::POST:
        return "POST";
      case HTTPMethods::PUT:
        return "PUT";
      case HTTPMethods::DELETE:
        return "DELETE";
      case HTTPMethods::HEAD:
        return "HEAD";
      case HTTPMethods::OPTIONS:
        return "OPTIONS";
      case HTTPMethods::TRACE:
        return "TRACE";
      case HTTPMethods::CONNECT:
        return "CONNECT";
      case HTTPMethods::PATCH:
        return "PATCH";
      case HTTPMethods::LINK:
        return "LINK";
      case HTTPMethods::UNLINK:
        return "UNLINK";
#ifdef COMPILE_TEST
      // value used only in the tests
      case HTTPMethods::FAKE_METHOD:
        return "FAKE_METHOD";
#endif
    }
  return "?";
}
