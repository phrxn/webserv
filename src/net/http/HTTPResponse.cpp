#include "HTTPResponse.hpp"

#include <sstream>

const std::string HTTPResponse::KEY_AND_VALUE_SEPARATOR = ": ";

HTTPResponse::HTTPResponse(SocketFileDescriptor *socketFD)
    : _socketFD(socketFD), _keepAlive(false) {
  (void)_socketFD;
}

HTTPResponse::~HTTPResponse() {}

// deleted (this class MUST BE UNIQUE!)
HTTPResponse::HTTPResponse(const HTTPResponse &src) { (void)src; }
// deleted (this class MUST BE UNIQUE!)
HTTPResponse &HTTPResponse::operator=(const HTTPResponse &src) {
  (void)src;
  return *this;
}

void HTTPResponse::createResponse() {

  std::string theResponse;

  theResponse += createResponseString();

  _socketFD->getOutputStream().assign(theResponse.begin(),
                                      theResponse.begin() + theResponse.size());
  _socketFD->setCloseSocketAfterProcessingResponse(_keepAlive);
}

void HTTPResponse::setHTTPVersion(const std::string &httpVersion) {
  _httpVersion = httpVersion;
}

void HTTPResponse::setStatus(HTTPStatus::Status status) {
  std::stringstream ss;

  HTTPStatus httpStatus;

  ss << status << " " << httpStatus.getStatusToString(status);

  _status = status;
  _statusStr = ss.str();
}

HTTPStatus::Status HTTPResponse::getStatus() const { return _status; }

std::string HTTPResponse::getStatusStr() const { return _statusStr; }

void HTTPResponse::setServer(const std::string &server) { _server = server; }

void HTTPResponse::setDate(const std::string &date) { _date = date; }

void HTTPResponse::setContentType(const std::string &contentType) {
  _contentType = contentType;
}

void HTTPResponse::setContentLength(const std::string &contentLength) {
  _contentLength = contentLength;
}

void HTTPResponse::setContentLength(std::size_t contentLength) {
  std::stringstream ss;

  ss << contentLength;
  setContentLength(ss.str());
}

void HTTPResponse::setLastModified(const std::string &lastModified) {
  _lastModified = lastModified;
}

void HTTPResponse::setConnection(const std::string &connection) {
  _connection = connection;
  _keepAlive = false;
  if (_connection == "keep-alive") {
	_keepAlive = true;
  }
}

bool HTTPResponse::getKeepAlive() const{
	return _keepAlive;
}

void HTTPResponse::addHeader(const std::string &key, const std::string &value) {
  _mapOtherHeaders[key] = value;
}

void HTTPResponse::setBody(const std::string &body) { _body = body; }

std::string HTTPResponse::createResponseString() {
  std::stringstream ss;

  ss << _httpVersion << " " << _statusStr << "\r\n";
  if (!_server.empty()) {
    ss << "Server" << KEY_AND_VALUE_SEPARATOR << _server << "\r\n";
  }
  if (!_date.empty()) {
    ss << "Date" << KEY_AND_VALUE_SEPARATOR << _date << "\r\n";
  }
  if (!_contentType.empty()) {
    ss << "Content-Type" << KEY_AND_VALUE_SEPARATOR << _contentType << "\r\n";
  }
  if (!_contentLength.empty()) {
    ss << "Content-Length" << KEY_AND_VALUE_SEPARATOR << _contentLength
       << "\r\n";
  }
  if (!_lastModified.empty()) {
    ss << "Last-Modified" << KEY_AND_VALUE_SEPARATOR << _lastModified << "\r\n";
  }
  if (!_connection.empty()) {
    ss << "Connection" << KEY_AND_VALUE_SEPARATOR << _connection << "\r\n";
  }

  std::map<std::string, std::string>::iterator it = _mapOtherHeaders.begin();
  std::map<std::string, std::string>::iterator end = _mapOtherHeaders.end();

  for (; it != end; ++it) {
    if (it->second.empty()) {
      continue;
    }
    ss << it->first << ": " << it->second << "\r\n";
  }

  ss << "\r\n";

  ss << _body;

  return ss.str();
}