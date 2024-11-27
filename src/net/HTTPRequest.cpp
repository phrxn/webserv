#include "HTTPRequest.hpp"

#include <iostream>

HTTPRequest::HTTPRequest(SocketFileDescriptor *socketFD)
    : _socketFD(socketFD) {
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