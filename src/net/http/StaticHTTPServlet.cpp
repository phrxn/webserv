#include "StaticHTTPServlet.hpp"

#include "StaticPagesPhysicalPathChecker.hpp"
#include "html/DirectoryHTMLDocument.hpp"
#include "html/FileHTMLDocument.hpp"
#include "ExtendedBehaviorStaticHTTP.hpp"

StaticHTTPServlet::StaticHTTPServlet(const VirtualHost *virtualHost, const URL &url)
    : _virtualHost(virtualHost),
	  _url(url),
	  _physicalPathChecker(new StaticPagesPhysicalPathChecker),
      _htmlDocument(NULL),
	  _programConfiguration(ProgramConfiguration::getInstance()) {

	_physicalPathToResource = virtualHost->getThePhysicalPath(url);

	_urlPathToDir = url.getPathFull(true);
	_canListDirectory = virtualHost->isDirectoryListingAllowedForThisPath(url);
}

StaticHTTPServlet::~StaticHTTPServlet() {
  if (_physicalPathChecker) {
    delete _physicalPathChecker;
  }
  if (_htmlDocument) {
    delete _htmlDocument;
  }
}

// deleted (this class MUST BE UNIQUE!)
StaticHTTPServlet::StaticHTTPServlet(const StaticHTTPServlet &src) : _url(src._url) {
  (void)src;
}

// deleted (this class MUST BE UNIQUE!)
StaticHTTPServlet &StaticHTTPServlet::operator=(const StaticHTTPServlet &src) {
  (void)src;
  return *this;
}

HTTPStatus::Status StaticHTTPServlet::doGet(HTTPRequest &request, HTTPResponse &response) {
  (void)request;
  HTTPStatus::Status status =
      _physicalPathChecker->isThePathValidForTheGetMethod(
          _physicalPathToResource, _canListDirectory);
  if (status != HTTPStatus::OK) {
    return status;
  }

  error::StatusOr<bool> isDirectory = _physicalPathChecker->isThePathAPathToADirectory(_physicalPathToResource);
  if (!isDirectory.ok()) {
    return HTTPStatus::INTERNAL_SERVER_ERROR;
  }

  bool isADirectory = isDirectory.value();
  if (isADirectory) {
    _htmlDocument = new DirectoryHTMLDocument(_physicalPathToResource, _urlPathToDir);
  } else {
    _htmlDocument = new FileHTMLDocument(_physicalPathToResource);
  }

  _fillHTTPResponse.makeFill(response, *_htmlDocument);
  return HTTPStatus::OK;
}

HTTPStatus::Status StaticHTTPServlet::doPost(HTTPRequest &request,
                                             HTTPResponse &response) {
	(void)response;
    HTTPStatus::Status statusToReturn = HTTPStatus::OK;

	std::string uploadFolderPath = _virtualHost->getUploadFolderPath(_url);
	std::string physicalRelativePath = _virtualHost->getTheRelativePhysicalPath(_url);

	if (_programConfiguration.isExtendedHttpBehavior() && !uploadFolderPath.empty()){
		ExtendedBehaviorStaticHTTP extesion;
		statusToReturn = extesion.doPost(physicalRelativePath, uploadFolderPath, request);
	}else{
		statusToReturn = _physicalPathChecker->isThePathValidForThePostMethod(_physicalPathToResource);
	}
  return statusToReturn;
}

HTTPStatus::Status StaticHTTPServlet::doDelete(HTTPRequest &request,
                                               HTTPResponse &response) {
  (void)response;
  (void)request;

  if (_programConfiguration.isExtendedHttpBehavior()){
	ExtendedBehaviorStaticHTTP extesion;
	return extesion.doDelete(_physicalPathToResource);
  }
  return _physicalPathChecker->isThePathValidForTheDeleteMethod(_physicalPathToResource);
}

bool StaticHTTPServlet::absolutePathEndsWithSlash(const std::string &absolutePathToResource){
	return (!absolutePathToResource.empty() && absolutePathToResource[absolutePathToResource.size() - 1] == '/');
}