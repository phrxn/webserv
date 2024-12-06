#include "URL.hpp"

#include <sstream>

const std::string URL::PROTOCOL_DELIMITER("://");
const std::string URL::PORT_DELIMITER(":");
const std::string URL::PATH_DELIMITER("/");
const std::string URL::QUERY_DELIMITER("?");

URL::URL()
    : _protocol(""),
      _domain(""),
      _port(0),
      _path(""),
      _query(""),
      _isURLValid(false) {}

URL::~URL() {}

URL::URL(const URL &src) { *this = src; }

URL &URL::operator=(const URL &src) {
  if (this == &src) return *this;

  _protocol = src._protocol;
  _domain = src._domain;
  _port = src._port;
  _path = src._path;
  _query = src._query;

  return *this;
}

bool URL::operator==(const URL &src) const {
  if (_protocol != src._protocol) {
    return false;
  }
  if (_domain != src._domain) {
    return false;
  }
  if (_port != src._port) {
    return false;
  }
  if (_path != src._path) {
    return false;
  }
  if (_query != src._query) {
    return false;
  }
  return true;
}

const std::string &URL::getProtocol() const { return _protocol; }

void URL::setProtocol(const std::string &protocol) { _protocol = protocol; }

int URL::getPort() const { return _port; }
void URL::setPort(int port) { _port = port; }

const std::string &URL::getDomain() const { return _domain; }
void URL::setDomain(const std::string &domain) { _domain = domain; }

const std::string &URL::getPath() const { return _path; }
void URL::setPath(const std::string &path) { _path = path; }

const std::string &URL::getQuery() const { return _query; }

void URL::setQuery(const std::string &query) { _query = query; }

void URL::parserStringToURL(std::string url) {
  _protocol = extractProtocol(url);
  _domain = extractDomain(url);
  std::string tmpPort = extractPort(url);

  std::stringstream sstring(tmpPort);
  sstring >> _port;

  _path = extractPath(url);
  _query = extractQuery(url);
}

std::string URL::extractProtocol(std::string &url) {
  std::string protocol;

  std::string::size_type delimiterIndex = url.find(PROTOCOL_DELIMITER);

  if (delimiterIndex != std::string::npos) {
    protocol = url.substr(0, delimiterIndex);
    url.erase(0, delimiterIndex + PROTOCOL_DELIMITER.size());
  }
  return protocol;
}

/*
  This method expects the URL string to already be without the protocol part,
  see: extractProtocol
*/
std::string URL::extractDomain(std::string &url) {
  std::string domain;

  std::string::size_type delimiterPathIndex = url.find(PATH_DELIMITER);
  if (delimiterPathIndex == 0) return "";

  std::string::size_type delimiterPortIndex = url.find(PORT_DELIMITER);

  // if the port delimiter was not found
  if (delimiterPortIndex == std::string::npos) {
    delimiterPortIndex = url.find(PATH_DELIMITER);
  }

  // if 0 the url start with "/" or
  // if npos all string a domain
  if (delimiterPortIndex == 0 || delimiterPortIndex == std::string::npos) {
    return url;
  }

  domain = url.substr(0, delimiterPortIndex);
  url.erase(0, delimiterPortIndex);

  return domain;
}

/*
  This method expects the URL string to already be without the domain part,
  see: extractDomain
*/
std::string URL::extractPort(std::string &url) {
  std::string port;

  std::string::size_type delimiterIndex = url.find(PORT_DELIMITER);

  // if the port delimiter was not found
  if (delimiterIndex == std::string::npos) {
    return url;
  }

  // remove PORT_DELIMITER
  url.erase(0, 1);

  std::string::size_type delimiterPath = url.find(PATH_DELIMITER);

  port = url.substr(0, delimiterPath);
  url.erase(0, delimiterPath);

  return port;
}

/*
  This method expects the URL string to already be without the protocol,domain
  and port part, see: extractDomain.

  The string MUST start with "/" character
*/
std::string URL::extractPath(std::string &url) {
  std::string path;

  std::string::size_type delimiterIndex = url.find(PATH_DELIMITER);
  if (delimiterIndex == std::string::npos || delimiterIndex != 0) {
    return url;
  }

  std::string::size_type delimiterQueryIndex = url.find(QUERY_DELIMITER);

  path = url.substr(0, delimiterQueryIndex);
  url.erase(0, delimiterQueryIndex);

  return path;
}

/*
  This method expects the URL string to already be without the protocol, domain,
  port and path part, see: extractPath.

  The string MUST start with "/" character
*/
std::string URL::extractQuery(std::string &url) {
  std::string query;

  std::string::size_type delimiterIndex = url.find(QUERY_DELIMITER);
  if (delimiterIndex == std::string::npos || delimiterIndex != 0) {
    return url;
  }

  // remove QUERY_DELIMITER
  url.erase(0, 1);
  query = url;
  url.clear();

  return query;
}

std::ostream &operator<<(std::ostream &os, const URL &url) {
  os << "[URL: protocol: " << url.getProtocol() << ", "
     << "domain: " << url.getDomain() << ", "
     << "port: " << url.getPort() << ", "
     << "path: " << url.getPath() << ", "
     << "query: " << url.getQuery() << "]";
  return os;
}

bool URL::isHexDigit(char c) {
  return (std::isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

char URL::hexToChar(const std::string &hex) {
  int value;
  std::stringstream ss;
  ss << std::hex << hex;
  ss >> value;
  return static_cast<char>(value);
}

std::string URL::decode(const std::string &input) {
  std::string result;
  for (size_t i = 0; i < input.length(); ++i) {
    if (input[i] == '%' && (i + 2 < input.length()) &&
        isHexDigit(input[i + 1]) && isHexDigit(input[i + 2])) {
      result += hexToChar(input.substr(i + 1, 2));
      i += 2;
    } else {
      result += input[i];
    }
  }
  return result;
}