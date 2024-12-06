#include "HTTPServletManager.hpp"

#include "../../error/Log.hpp"
#include "../VirtualHostFactory.hpp"
#include "HTTPServletCGI.hpp"
#include "HTTPServletStatic.hpp"

HTTPServletManager::HTTPServletManager(SocketFileDescriptor *socketFD,
                                       Log *logger)
    : _hTTPServlet(NULL),
      _virtualHost(NULL),
      _socketFD(socketFD),
      _logger(logger) {}

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
  _virtualHost = vhf.createVirtualHost(request.getHost());

  if (request.getStatus() != OK) {
    return doError(request.getStatus(), response);
  }

  if (_virtualHost->isUrlAPathToCGI(request.getURL())) {
    _hTTPServlet = new HTTPServletCGI(_virtualHost);
  } else {
    _hTTPServlet = new HTTPServletStatic(_virtualHost);
  }

  switch (request.getMethod()) {
    case GET:
      _hTTPServlet->doGet(request, response);
      break;
    case POST:
      _hTTPServlet->doPost(request, response);
      break;
    case DELETE:
      _hTTPServlet->doDelete(request, response);
      break;
    default:
      _logger->log(Log::FATAL, "HTTPServletManager", "doService",
                   "an HTTP verb passed through the filters on the fd",
                   _socketFD->getFileDescriptor());
	  _logger->log(Log::FATAL, "HTTPServletManager", "doService",
                   "the verb value", request.getMethod());
      response.setStatus(NOT_IMPLEMENTED);
      break;
  }

  if (response.getStatus() != OK) {
    doError(response.getStatus(), response);
  }
}

void HTTPServletManager::doError(HTTPStatus httpStatus,
                                 HTTPResponse &response) {
  (void)httpStatus;
  (void)response;
}