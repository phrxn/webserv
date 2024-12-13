#include "HTTPRequest.hpp"

#include <iostream>

HTTPRequest::HTTPRequest(SocketFileDescriptor *socketFD) : _socketFD(socketFD) {
  (void)_socketFD;
  (void)_buffer;
}

HTTPRequest::~HTTPRequest() {}

// deleted (this class MUST BE UNIQUE!)
HTTPRequest::HTTPRequest(const HTTPRequest &src) { (void)src; }

// deleted (this class MUST BE UNIQUE!)
HTTPRequest &HTTPRequest::operator=(const HTTPRequest &src) {
  (void)src;
  return *this;
}

HTTPRequest::StateOfCreation HTTPRequest::createRequest() {
  return REQUEST_CREATED;
}

std::string HTTPRequest::getHost() const { return ""; }

HTTPMethods::Method HTTPRequest::getMethod() const {
	return HTTPMethods::GET;
}

URL HTTPRequest::getURL() const {
	return _url;
}

HTTPStatus::Status HTTPRequest::getStatus() const {
	return HTTPStatus::OK;
}

std::string HTTPRequest::getContentLength() const{
	return "";
}

std::string HTTPRequest::getContentType() const{
	return "";
}