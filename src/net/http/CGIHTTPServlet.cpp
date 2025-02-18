#include "CGIHTTPServlet.hpp"

#include "CGIPagesPhysicalPathChecker.hpp"
#include "cgi/ExecuteCGIProgram.hpp"
#include "html/CGIHTMLDocument.hpp"

CGIHTTPServlet::CGIHTTPServlet(const VirtualHost *virtualHost, const URL &url)
    : _physicalPathChecker(new CGIPagesPhysicalPathChecker),
      _htmlDocument(NULL) {
  _physicalPathToResource = virtualHost->getThePhysicalPath(url);
  _rootVirtualHostLocation = virtualHost->getRootDir(url);
}

CGIHTTPServlet::~CGIHTTPServlet() {
  if (_physicalPathChecker) {
    delete _physicalPathChecker;
  }
  if (_htmlDocument) {
    delete _htmlDocument;
  }
}

// deleted (this class MUST BE UNIQUE!)
CGIHTTPServlet::CGIHTTPServlet(const CGIHTTPServlet &src) { *this = src; }

// deleted (this class MUST BE UNIQUE!)
CGIHTTPServlet &CGIHTTPServlet::operator=(const CGIHTTPServlet &src) {
  (void)src;
  return *this;
}

HTTPStatus::Status CGIHTTPServlet::doGet(HTTPRequest &request,
                                         HTTPResponse &response) {
  return makePage(request, response);
}

HTTPStatus::Status CGIHTTPServlet::doPost(HTTPRequest &request,
                                          HTTPResponse &response) {
  return makePage(request, response);
  ;
}

HTTPStatus::Status CGIHTTPServlet::doDelete(HTTPRequest &request,
                                            HTTPResponse &response) {
  return makePage(request, response);
}

HTTPStatus::Status CGIHTTPServlet::makePage(HTTPRequest &request,
                                            HTTPResponse &response) {
  (void)response;

  // check if the file exists and can be read
  HTTPStatus::Status status =
      _physicalPathChecker->isThePathValidForTheGetMethod(
          _physicalPathToResource, false);
  if (status != HTTPStatus::OK) {
    return status;
  }

  CGIHTMLDocument _cgiHTMLDocument(response);

  HTTPStatus::Status statusCreatePage = _cgiHTMLDocument.createPage(
      _rootVirtualHostLocation, _physicalPathToResource, request);

  if (statusCreatePage == HTTPStatus::OK) {
    _fillHTTPResponse.makeFill(response, _cgiHTMLDocument);
  }

  return statusCreatePage;
}
