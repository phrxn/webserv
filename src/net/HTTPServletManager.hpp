#ifndef NET_HTTP_SERVLET_MANAGER_HPP
#define NET_HTTP_SERVLET_MANAGER_HPP

#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include "HTTPServlet.hpp"
#include "SocketFileDescriptor.hpp"

class HTTPServletManager {
 public:
  HTTPServletManager(SocketFileDescriptor *socketFD);
  ~HTTPServletManager();
  void doService(HTTPRequest &request, HTTPResponse &response);
  void doError(int CodeError, HTTPResponse &response);

 private:
  HTTPServletManager(const HTTPServletManager &src);
  HTTPServletManager &operator=(const HTTPServletManager &src);

  HTTPServlet *_hTTPServlet;
};

#endif