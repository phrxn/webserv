#include "HTTPServletManager.hpp"

#include "../../config/ProgramConfiguration.hpp"
#include "../../error/Log.hpp"
#include "../VirtualHostFactory.hpp"
#include "HTTPServletCGI.hpp"
#include "HTTPServletStatic.hpp"

HTTPServletManager::HTTPServletManager(SocketFileDescriptor *socketFD,
                                       Log *logger)
    : _hTTPServlet(NULL), _socketFD(socketFD), _logger(logger) {}

HTTPServletManager::~HTTPServletManager() {
  if (_hTTPServlet) delete _hTTPServlet;
}

// deleted (this class MUST BE UNIQUE!)
HTTPServletManager::HTTPServletManager(const HTTPServletManager &src) {
  (void)src;
}

// deleted (this class MUST BE UNIQUE!)
HTTPServletManager &HTTPServletManager::operator=(
    const HTTPServletManager &src) {
  (void)src;
  return *this;
}

void HTTPServletManager::doService(HTTPRequest &request, HTTPResponse &response) {

  _virtualHost = VirtualHostFactory().getVirtualHost(request.getPort(), request.getHost());

  HandlerHTTPStatus _handlerHTTPStatus(_virtualHost);

  URL url(request.getURLStr());

  HTTPStatus::Status validRequest = checkIfRequestIsValid(_virtualHost, request);

  if (validRequest != HTTPStatus::OK) {
	if (validRequest == HTTPStatus::MOVED_PERMANENTLY) {
		return _handlerHTTPStatus.doStatusFamily300(response, validRequest, _virtualHost->isPathARedirection(url));
	}
	return _handlerHTTPStatus.doStatusError(response, validRequest);
  }

  std::string absolutePathToResource = _virtualHost->getThePhysicalPath(url);

  _logger->log(Log::DEBUG, "HTTPServletManager", "doService", "absolute path to resource", absolutePathToResource);

  // If nothing is returned, then the URL did not match any possible location, so there is nothing to search for
  if (absolutePathToResource.empty()) {
    return _handlerHTTPStatus.doStatusError(response, HTTPStatus::NOT_FOUND);
  }

  bool pathPointsToCGI = _virtualHost->isUrlAPathToCGI(url);

 // If the path does not point to a CGI and it ends with "/" we can search for an index file
 // Why can't you search for an index file in a path that ends with a slash and is CGI?
 // Because what comes after the path to the CGI script is an extra path to the same
 // according to RFC CGI 1.1
  if (!pathPointsToCGI){
	std::string indexFile = _virtualHost->getIndexFile(url);

	if (absolutePathEndsWithSlash(absolutePathToResource) && !indexFile.empty()) {
		std::string absolutePathToIndexFile = absolutePathToResource + indexFile;

		File file(absolutePathToIndexFile);
		if (file.exist()) {
			absolutePathToResource = absolutePathToIndexFile;
			url.parserStringToURL(request.getURLStr() + indexFile);
			pathPointsToCGI = _virtualHost->isUrlAPathToCGI(url);
		}
	}
  }

  bool canListDirectory = _virtualHost->isDirectoryListingAllowedForThisPath(url);

  if (pathPointsToCGI) {
    _hTTPServlet = new HTTPServletCGI(absolutePathToResource, _virtualHost->getRootDir(url));
  } else {
    _hTTPServlet = new HTTPServletStatic(absolutePathToResource, url.getPathFull(false), canListDirectory);
  }

  // based on the http verb call the corresponding method
  HTTPStatus::Status methodReturn = executeMethod(_hTTPServlet, request, response);

  if (methodReturn == HTTPStatus::OK) {
    return _handlerHTTPStatus.doStatusFamily200(request, response, methodReturn);
  }

  // If the methodReturn return was 301, at this point in the code, it means that the
  // redirection is due to the lack of a slash in some path to a directory
  if (methodReturn == HTTPStatus::MOVED_PERMANENTLY) {
    return _handlerHTTPStatus.doStatusFamily300(response, methodReturn, url.getPathFull(true) + "/");
  }

  _handlerHTTPStatus.doStatusError(response, methodReturn);
}


void HTTPServletManager::doError(HTTPStatus::Status status, HTTPResponse &response){

  VirtualHostFactory vhf;

  HandlerHTTPStatus _handlerHTTPStatus(NULL);

  _handlerHTTPStatus.doStatusError(response, status);
}


bool HTTPServletManager::absolutePathEndsWithSlash(const std::string &absolutePathToResource){
	return (!absolutePathToResource.empty() && absolutePathToResource[absolutePathToResource.size() - 1] == '/');
}


HTTPStatus::Status HTTPServletManager::executeMethod(HTTPServlet *_hTTPServlet, HTTPRequest &request, HTTPResponse &response){

	// based on the http verb call the corresponding method
	HTTPStatus::Status methodReturn = HTTPStatus::INTERNAL_SERVER_ERROR;
	switch (request.getMethod()) {
	  case HTTPMethods::GET:
		methodReturn = _hTTPServlet->doGet(request, response);
		break;
	  case HTTPMethods::POST:
		methodReturn = _hTTPServlet->doPost(request, response);
		break;
	  case HTTPMethods::DELETE:
		methodReturn = _hTTPServlet->doDelete(request, response);
		break;
	  default:
		_logger->log(Log::FATAL, "HTTPServletManager", "doService", "an HTTP verb passed through the filters on the fd", _socketFD->getFileDescriptor());
		_logger->log(Log::FATAL, "HTTPServletManager", "doService", "the verb value", request.getMethod());
		methodReturn = HTTPStatus::NOT_IMPLEMENTED;
		break;
	}
	return methodReturn;
}

HTTPStatus::Status HTTPServletManager::checkIfRequestIsValid(const VirtualHostDefault *virtualHost, HTTPRequest &request){

	URL url(request.getURLStr());

	if (request.getStatus() != HTTPStatus::OK) {
		return request.getStatus();
	}

	if (request.getBody().size() > virtualHost->getLimitBodySizeInBytes()) {
		return HTTPStatus::REQUEST_ENTITY_TOO_LARGE;
	}

	if (!virtualHost->isPathValid(url)) {
		return HTTPStatus::NOT_FOUND;
	}

	if (!virtualHost->isPathARedirection(url).empty()) {
		return HTTPStatus::MOVED_PERMANENTLY;
	}

	if (!ProgramConfiguration::getInstance().theServerSupportsThisHTTPMethod(request.getMethod())) {
		return HTTPStatus::NOT_IMPLEMENTED;
	}

	if (!virtualHost->isTheMethodAllowedForThisPath(url, request.getMethod())) {
		return HTTPStatus::NOT_ALLOWED;
	}

	return HTTPStatus::OK;
}