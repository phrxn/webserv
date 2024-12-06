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

std::string HTTPRequest::getHost() { return ""; }

HTTPMethods::Method HTTPRequest::getMethod(){
	return HTTPMethods::GET;
}

std::string HTTPRequest::getURL(){
	return "";
}

HTTPStatus::Status HTTPRequest::getStatus(){
	return HTTPStatus::OK;
}
