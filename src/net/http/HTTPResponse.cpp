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

  if(_status != HTTPStatus::INVALID && _isItACGIResponse){
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

void HTTPResponse::setHeaders(const std::map<std::string, std::vector<std::string> > &headers){
	_headers = headers;
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

bool HTTPResponse::setConnection(const std::string &connection) {
  if (!_addHeader("Connection", connection)){
	return false;
  }
  _closeConnectionAfterThatResponse = true;
  if (connection == "keep-alive") {
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

bool HTTPResponse::_addHeader(const std::string &key, const std::string &value) {
  std::map<std::string, std::vector<std::string> >::iterator theKey = _headers.find(key);
  if (theKey != _headers.end() && _isItACGIResponse) {
    return false;
  }
  _headers[key].push_back(value);
  return true;
}

std::ostream &operator<<(std::ostream &os, const HTTPResponse &response){
	os << response.createResponseString();
	return os;
}