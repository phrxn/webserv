#include "HTTPServletStatic.hpp"

HTTPServletStatic::HTTPServletStatic(const VirtualHost *virtualHost)
    : _virtualHost(virtualHost) {
		(void)_virtualHost;
	}

HTTPServletStatic::~HTTPServletStatic() {}

// deleted (this class MUST BE UNIQUE!)
HTTPServletStatic::HTTPServletStatic(const HTTPServletStatic &src) {
  (void)src;
}

// deleted (this class MUST BE UNIQUE!)
HTTPServletStatic &HTTPServletStatic::operator=(const HTTPServletStatic &src) {
  (void)src;
  return *this;
}

void HTTPServletStatic::doGet(HTTPRequest &request, HTTPResponse &response) {
  (void)request;
  (void)response;
}

void HTTPServletStatic::doPost(HTTPRequest &request, HTTPResponse &response) {
  (void)request;
  (void)response;
}

void HTTPServletStatic::doDelete(HTTPRequest &request, HTTPResponse &response) {
  (void)request;
  (void)response;
}