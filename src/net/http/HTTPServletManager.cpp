#include "HTTPServletManager.hpp"

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

void HTTPServletManager::doService(HTTPRequest &request,
                                   HTTPResponse &response) {
  VirtualHostFactory vhf;

  _virtualHost = vhf.getVirtualHost(request.getPort(), request.getHost());

  HandlerHTTPStatus _handlerHTTPStatus(_virtualHost);

  if (request.getStatus() != HTTPStatus::OK) {
    return _handlerHTTPStatus.doStatusError(response, request.getStatus());
  }

  URL url;
  url.parserStringToURL(request.getURL());

  if (!_virtualHost.isPathValid(url)) {
    return _handlerHTTPStatus.doStatusError(response, HTTPStatus::NOT_FOUND);
  }

  std::string pathRedirection = _virtualHost.isPathARedirection(url);
  if (pathRedirection != "") {
    return _handlerHTTPStatus.doStatusFamily300(
        response, HTTPStatus::MOVED_PERMANENTLY, pathRedirection);
  }

  if (!_virtualHost.isTheMethodAllowedForThisPath(url, request.getMethod())) {
    return _handlerHTTPStatus.doStatusError(response, HTTPStatus::NOT_ALLOWED);
  }

  bool pathPointsToCGI = _virtualHost.isUrlAPathToCGI(url);
  std::string absolutePathToResource = _virtualHost.getThePhysicalPath(url);
  _logger->log(Log::DEBUG, "HTTPServletManager", "doService",
                   "absolute path to resource", absolutePathToResource);

  bool canListDirectory =
      _virtualHost.isDirectoryListingAllowedForThisPath(url);

  if (pathPointsToCGI) {
    _hTTPServlet = new HTTPServletCGI(_virtualHost);
  } else {
    _hTTPServlet =
        new HTTPServletStatic(absolutePathToResource, url.getPath(), canListDirectory);
  }

  HTTPStatus::Status methodReturn = HTTPStatus::SERVER_ERROR;
  // based on the http verb call the corresponding method
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
      _logger->log(Log::FATAL, "HTTPServletManager", "doService",
                   "an HTTP verb passed through the filters on the fd",
                   _socketFD->getFileDescriptor());
      _logger->log(Log::FATAL, "HTTPServletManager", "doService",
                   "the verb value", request.getMethod());
      methodReturn = HTTPStatus::NOT_IMPLEMENTED;
      break;
  }

  if (methodReturn == HTTPStatus::OK) {
    return _handlerHTTPStatus.doStatusFamily200(request, response,
                                                methodReturn);
  }

  // If the return was 301, at this point in the code, it means that the
  // redirection is due to the lack of a slash in some path to a directory
  if (methodReturn == HTTPStatus::MOVED_PERMANENTLY) {
    return _handlerHTTPStatus.doStatusFamily300(response, methodReturn,
                                                url.getPath() + "/");
  }

  _handlerHTTPStatus.doStatusError(response, methodReturn);
}

void HTTPServletManager::doError(HTTPStatus::Status status, HTTPResponse &response){

  VirtualHostFactory vhf;

  VirtualHostDefault _virtualHost = vhf.getDefaultVirtualHost();

  HandlerHTTPStatus _handlerHTTPStatus(_virtualHost);

  _handlerHTTPStatus.doStatusError(response, status);
}