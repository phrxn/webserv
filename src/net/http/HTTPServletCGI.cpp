#include "HTTPServletCGI.hpp"

#include "CGIPagesPhysicalPathChecker.hpp"

#include "html/CGIHTMLDocument.hpp"

#include "cgi/ExecuteCGIProgram.hpp"

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
  return makePage(request, response);
}

HTTPStatus::Status HTTPServletCGI::doPost(HTTPRequest &request,
                                          HTTPResponse &response) {
  return makePage(request, response);;
}

HTTPStatus::Status HTTPServletCGI::doDelete(HTTPRequest &request,
                                            HTTPResponse &response) {
  return makePage(request, response);
}

HTTPStatus::Status HTTPServletCGI::makePage(HTTPRequest &request, HTTPResponse &response){
  (void)response;

  //check if the file exists and can be read
  HTTPStatus::Status status = _physicalPathChecker->isThePathValidForTheGetMethod(_physicalPathToResource, false);
  if (status != HTTPStatus::OK) {
    return status;
  }

  CGIHTMLDocument _cgiHTMLDocument(response);

  HTTPStatus::Status statusCreatePage = _cgiHTMLDocument.createPage(_rootVirtualHostLocation, _physicalPathToResource, request);

  _fillHTTPResponse.makeFill(response, _cgiHTMLDocument);

  return statusCreatePage;
}
