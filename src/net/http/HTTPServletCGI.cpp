#include "HTTPServletCGI.hpp"

HTTPServletCGI::HTTPServletCGI(const VirtualHost virtualHost)
    : _virtualHost(virtualHost) {
  (void)_virtualHost;
}

HTTPServletCGI::~HTTPServletCGI() {}

// deleted (this class MUST BE UNIQUE!)
HTTPServletCGI::HTTPServletCGI(const HTTPServletCGI &src) { *this = src; }

// deleted (this class MUST BE UNIQUE!)
HTTPServletCGI &HTTPServletCGI::operator=(const HTTPServletCGI &src) {
  (void)src;
  return *this;
}

void HTTPServletCGI::doGet(HTTPRequest &request, HTTPResponse &response) {
  (void)request;
  (void)response;
}

void HTTPServletCGI::doPost(HTTPRequest &request, HTTPResponse &response) {
  (void)request;
  (void)response;
}

void HTTPServletCGI::doDelete(HTTPRequest &request, HTTPResponse &response) {
  (void)request;
  (void)response;
}
