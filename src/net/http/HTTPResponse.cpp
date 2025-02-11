#include "HTTPResponse.hpp"

#include <sstream>

const std::string HTTPResponse::KEY_AND_VALUE_SEPARATOR = ": ";

HTTPResponse::HTTPResponse(SocketFileDescriptor *socketFD)
    : _socketFD(socketFD),
      _status(HTTPStatus::INVALID),
      _closeConnectionAfterThatResponse(true),
      _isItACGIResponse(false) {}

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
  _socketFD->setCloseSocketAfterProcessingResponse(
      _closeConnectionAfterThatResponse);
}

void HTTPResponse::setHTTPVersion(const std::string &httpVersion) {
  _httpVersion = httpVersion;
}

void HTTPResponse::setStatus(HTTPStatus::Status status) {
  if (_status != HTTPStatus::INVALID && _isItACGIResponse) {
    return;
  }

  std::stringstream ss;

  HTTPStatus httpStatus;

  ss << status << " " << httpStatus.getStatusToString(status);

  _status = status;
  _statusStr = ss.str();
}

HTTPStatus::Status HTTPResponse::getStatus() const { return _status; }

std::string HTTPResponse::getStatusStr() const { return _statusStr; }

void HTTPResponse::setHeaders(
    const std::map<std::string, std::vector<std::string> > &headers) {
  std::map<std::string, std::vector<std::string> >::const_iterator it;
  for (it = headers.begin(); it != headers.end(); ++it) {
    std::vector<std::string>::const_iterator valueIt = it->second.begin();
    if (valueIt->empty()) {
      continue;
    }
    for (; valueIt != it->second.end(); ++valueIt) {
      _addHeader(it->first, *valueIt);
    }
  }
}

bool HTTPResponse::setServer(const std::string &server) {
  return _addHeader("Server", server);
}

bool HTTPResponse::setDate(const std::string &date) {
  return _addHeader("Date", date);
}

bool HTTPResponse::setContentType(const std::string &contentType) {
  return _addHeader("Content-Type", contentType);
}

bool HTTPResponse::setContentLength(const std::string &contentLength) {
  return _addHeader("Content-Length", contentLength);
}

bool HTTPResponse::setContentLength(std::size_t contentLength) {
  std::stringstream ss;

  ss << contentLength;
  return setContentLength(ss.str());
}

bool HTTPResponse::setLastModified(const std::string &lastModified) {
  return _addHeader("Last-Modified", lastModified);
}

#include <iostream>
bool HTTPResponse::setConnection(const std::string &connection) {

  std::cout << "Connection: " << connection << std::endl;

  std::string theConnection = connection;

  for (size_t i = 0; i < theConnection.size(); ++i) {
    if (i == 0) {
      continue;
    }
    theConnection[i] = std::tolower(theConnection[i]);
  }

  if (connection.empty()){
	theConnection = "close";
  }

  if (!_addHeader("Connection", theConnection)) {
    return false;
  }

  _closeConnectionAfterThatResponse = true;
  if (theConnection == "keep-alive") {
    _closeConnectionAfterThatResponse = false;
  }
  return true;
}

bool HTTPResponse::closeConnectionAfterThatResponse() const {
  return _closeConnectionAfterThatResponse;
}

bool HTTPResponse::addHeader(const std::string &key, const std::string &value) {
  return _addHeader(key, value);
}

void HTTPResponse::setBody(const std::string &body) { _body = body; }

std::string HTTPResponse::createResponseString() const {
  std::stringstream ss;

  ss << _httpVersion << " " << _statusStr << "\r\n";

  std::map<std::string, std::vector<std::string> >::const_iterator it;
  for (it = _headers.begin(); it != _headers.end(); ++it) {
    std::vector<std::string>::const_iterator valueIt = it->second.begin();
    if (valueIt->empty()) {
      continue;
    }
    for (; valueIt != it->second.end(); ++valueIt) {
      ss << it->first << ": " << *valueIt << "\r\n";
    }
  }
  ss << "\r\n";

  ss << _body;

  return ss.str();
}

void HTTPResponse::setItACGIResponse(bool isItACGIResponse) {
  _isItACGIResponse = isItACGIResponse;
}

bool HTTPResponse::_addHeader(const std::string &key,
                              const std::string &value) {
  std::string keyLowerCase = key;

  for (size_t i = 0; i < keyLowerCase.size(); ++i) {
    if (i == 0) {
      continue;
    }
    keyLowerCase[i] = std::tolower(keyLowerCase[i]);
  }

  std::map<std::string, std::vector<std::string> >::iterator theKey = _headers.find(keyLowerCase);
  if (theKey != _headers.end() && _isItACGIResponse) {
    return false;
  }
  _headers[keyLowerCase].push_back(value);
  return true;
}

std::ostream &operator<<(std::ostream &os, const HTTPResponse &response) {
  os << response.createResponseString();
  return os;
}