#include "URL.hpp"

#include <sstream>

const std::string URL::PROTOCOL_DELIMITER("://");
const std::string URL::PORT_DELIMITER(":");
const std::string URL::PATH_DELIMITER("/");
const std::string URL::QUERY_DELIMITER("?");

URL::URL(const std::string &urlEncoded){
	parserStringToURL(urlEncoded);
}

URL::URL()
    : _protocol(""),
      _domain(""),
      _port(0),
      _path(""),
      _query(""){}

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

void URL::setPathFull(const std::string &path) { _path = path; }



std::string URL::getPathFull(bool decoded) const{
	if (decoded){
		return decode(_path);
	}
	return _path;
}

/**
 * @brief Return the path without the extra path, return the path without the extra path, if the page type is not STATIC
 *
 * Exemple 1: /a/b.php/more/path -> /a/b.php
 * Exemple 2: /a/b.php -> /a/b.php
 */
std::string URL::getPath(bool decoded) const{

    std::string pathToReturn = _path;

    HTTPTypeOfPages::TypeOfPage typeOfPage = _httpTypeOfPages.getTypeOfPathFromPath(_path);
	if (typeOfPage != HTTPTypeOfPages::STATIC){
		std::string extension = _httpTypeOfPages.getTypeOfPageToString(typeOfPage);
		size_t extension_index = _path.find(extension);
		pathToReturn = _path.substr(0, extension_index + extension.length());
	}

	if (decoded){
		return decode(pathToReturn);
	}
	return pathToReturn;
}

/**
 * @brief Return the extra path from the full path, if the page type is not STATIC
 *
 * Exemple 1: /a/b.php/more/path -> /more/path
 * Exemple 2: /a/b.php -> ""
 */
std::string URL::getExtraPathFromFullPath() const{
	HTTPTypeOfPages::TypeOfPage typeOfPage = _httpTypeOfPages.getTypeOfPathFromPath(_path);
	if (typeOfPage == HTTPTypeOfPages::STATIC){
		return "";
	}
	return removePathToExtraPath(_path, typeOfPage);
}


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
    delimiterPortIndex = url.size();
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
     << "path: " << url.getPathFull(true) << ", "
     << "query: " << url.getQuery() << "]";
  return os;
}

bool URL::isHexDigit(char c) const {
  return (std::isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

char URL::hexToChar(const std::string &hex) const {
  int value;
  std::stringstream ss;
  ss << std::hex << hex;
  ss >> value;
  return static_cast<char>(value);
}

std::string URL::decode(const std::string &input) const {
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


//TESTAR ISSO
std::string URL::removePathToExtraPath(const std::string& pathFull, HTTPTypeOfPages::TypeOfPage typeOfPage) const {
	if (typeOfPage == HTTPTypeOfPages::STATIC){
		return "";
	}

    std::string extension = _httpTypeOfPages.getTypeOfPageToString(typeOfPage);
	if (pathFull < extension){
		return "";
	}

    size_t pos = pathFull.find(extension);
    if (pos != std::string::npos && pos + extension.length() < pathFull.length()) {
        return pathFull.substr(pos + extension.length());
    }
    return "";  // Retorna vazio se o delimitador não for encontrado ou estiver no final da string
}