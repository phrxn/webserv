#include "HTTPServletCGI.hpp"

#include "CGIPagesPhysicalPathChecker.hpp"

HTTPServletCGI::HTTPServletCGI(const std::string &physicalPathToResource, const std::string &rootVirtualHostLocation)
    : _physicalPathToResource(physicalPathToResource),
	  _rootVirtualHostLocation(rootVirtualHostLocation),
	  _physicalPathChecker(new CGIPagesPhysicalPathChecker),
      _htmlDocument(NULL){}

HTTPServletCGI::~HTTPServletCGI() {
  if (_physicalPathChecker) {
    delete _physicalPathChecker;
  }
  if (_htmlDocument) {
    delete _htmlDocument;
  }
}

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
