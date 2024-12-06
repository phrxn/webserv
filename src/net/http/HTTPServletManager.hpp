#ifndef NET_HTTP_HTTP_SERVLET_MANAGER_HPP
#define NET_HTTP_HTTP_SERVLET_MANAGER_HPP

#include "../../error/Log.hpp"
#include "../SocketFileDescriptor.hpp"
#include "../VirtualHost.hpp"
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include "HTTPServlet.hpp"
#include "HTTPStatus.hpp"

class HTTPServletManager {
 public:
  HTTPServletManager(SocketFileDescriptor *socketFD, Log *logger);
  ~HTTPServletManager();
  void doService(HTTPRequest &request, HTTPResponse &response);
  void doError(HTTPStatus httpStatus, HTTPResponse &response);

 private:
  HTTPServletManager(const HTTPServletManager &src);
  HTTPServletManager &operator=(const HTTPServletManager &src);

  HTTPServlet *_hTTPServlet;
  const VirtualHost *_virtualHost;
  SocketFileDescriptor *_socketFD;
  Log *_logger;

};

#endif