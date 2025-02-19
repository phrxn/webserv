#ifndef NET_HTTP_HTTP_SERVLET_MANAGER_HPP
#define NET_HTTP_HTTP_SERVLET_MANAGER_HPP

#include "../../error/Log.hpp"
#include "../SocketFileDescriptor.hpp"
#include "../VirtualHostDefault.hpp"
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include "HTTPServlet.hpp"
#include "HTTPStatus.hpp"
#include "HandlerHTTPStatus.hpp"

class HTTPServletManager {
 public:
  HTTPServletManager(SocketFileDescriptor *socketFD, Log *logger);
  ~HTTPServletManager();
  void doService(HTTPRequest &request, HTTPResponse &response);
  void doError(HTTPStatus::Status status, HTTPResponse &response);
  HTTPStatus::Status executeMethod(HTTPServlet *_hTTPServlet, HTTPRequest &request, HTTPResponse &response);
  HTTPStatus::Status checkIfRequestIsValid(const VirtualHostDefault *virtualHost, HTTPRequest &request);
  bool absolutePathEndsWithSlash(const std::string &absolutePathToResource);

 private:
  HTTPServletManager(const HTTPServletManager &src);
  HTTPServletManager &operator=(const HTTPServletManager &src);

  HTTPServlet *_hTTPServlet;
  const VirtualHostDefault *_virtualHost;
  SocketFileDescriptor *_socketFD;
  Log *_logger;


};

#endif