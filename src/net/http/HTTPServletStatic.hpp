#ifndef NET_HTTP_HTTP_SERVLET_STATIC_HPP
#define NET_HTTP_HTTP_SERVLET_STATIC_HPP

#include "HTTPServlet.hpp"

#include "../VirtualHost.hpp"

class HTTPServletStatic : public HTTPServlet {
 public:
  HTTPServletStatic(const VirtualHost *_virtualHost);
  ~HTTPServletStatic();

  void doGet(HTTPRequest &request, HTTPResponse &response);
  void doPost(HTTPRequest &request, HTTPResponse &response);
  void doDelete(HTTPRequest &request, HTTPResponse &response);

 private:
  HTTPServletStatic(const HTTPServletStatic &src);
  HTTPServletStatic &operator=(const HTTPServletStatic &src);

  const VirtualHost *_virtualHost;
};

#endif