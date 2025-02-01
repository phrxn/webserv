#include "HTTPServletStatic.hpp"

#include "html/DirectoryHTMLDocument.hpp"
#include "html/FileHTMLDocument.hpp"
#include "StaticPagesPhysicalPathChecker.hpp"

HTTPServletStatic::HTTPServletStatic(const std::string &physicalPathToResource,
                                     bool canListDirectory)
    : _physicalPathToResource(physicalPathToResource),
      _canListDirectory(canListDirectory),
      _physicalPathChecker(new StaticPagesPhysicalPathChecker),
      _htmlDocument(NULL) {}

HTTPServletStatic::~HTTPServletStatic() {
  if (_physicalPathChecker) {
    delete _physicalPathChecker;
  }
  if (_htmlDocument) {
    delete _htmlDocument;
  }
}

// deleted (this class MUST BE UNIQUE!)
HTTPServletStatic::HTTPServletStatic(const HTTPServletStatic &src) {
  (void)src;
}

// deleted (this class MUST BE UNIQUE!)
HTTPServletStatic &HTTPServletStatic::operator=(const HTTPServletStatic &src) {
  (void)src;
  return *this;
}

HTTPStatus::Status HTTPServletStatic::doGet(HTTPRequest &request,
                                            HTTPResponse &response) {
  (void)request;
  HTTPStatus::Status status =
      _physicalPathChecker->isThePathValidForTheGetMethod(
          _physicalPathToResource, _canListDirectory);
  if (status != HTTPStatus::OK) {
    return status;
  }

  error::StatusOr<bool> isDirectory =
      _physicalPathChecker->isThePathAPathToADirectory(_physicalPathToResource);
  if (!isDirectory.ok()) {
    return HTTPStatus::SERVER_ERROR;
  }

  bool isADirectory = isDirectory.value();
  if (isADirectory) {
    _htmlDocument = new DirectoryHTMLDocument(_physicalPathToResource);
  } else {
    _htmlDocument = new FileHTMLDocument(_physicalPathToResource);
  }

  _fillHTTPResponse.makeFill(response, *_htmlDocument);
  return HTTPStatus::OK;
}

HTTPStatus::Status HTTPServletStatic::doPost(HTTPRequest &request,
                                             HTTPResponse &response) {
  (void)request;
  (void)response;
  return _physicalPathChecker->isThePathValidForThePostMethod(
	  _physicalPathToResource);
}

HTTPStatus::Status HTTPServletStatic::doDelete(HTTPRequest &request,
                                               HTTPResponse &response) {
  (void)request;
  (void)response;
  return _physicalPathChecker->isThePathValidForTheDeleteMethod(
	  _physicalPathToResource);
}