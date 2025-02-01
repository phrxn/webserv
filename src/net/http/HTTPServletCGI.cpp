#include "HTTPServletCGI.hpp"

HTTPServletCGI::HTTPServletCGI(const VirtualHostDefault virtualHost)
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

HTTPStatus::Status HTTPServletCGI::doGet(HTTPRequest &request,
                                         HTTPResponse &response) {
  (void)request;
  (void)response;
  return HTTPStatus::OK;
}

HTTPStatus::Status HTTPServletCGI::doPost(HTTPRequest &request,
                                          HTTPResponse &response) {
  (void)request;
  (void)response;
  return HTTPStatus::OK;
}

HTTPStatus::Status HTTPServletCGI::doDelete(HTTPRequest &request,
                                            HTTPResponse &response) {
  (void)request;
  (void)response;
  return HTTPStatus::OK;
}
