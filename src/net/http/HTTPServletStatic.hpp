#ifndef NET_HTTP_HTTP_SERVLET_STATIC_HPP
#define NET_HTTP_HTTP_SERVLET_STATIC_HPP

#include "HTTPServlet.hpp"

class HTTPServletStatic : public HTTPServlet {
 public:
  HTTPServletStatic();
  ~HTTPServletStatic();

  void doGet(HTTPRequest &request, HTTPResponse &response);
  void doPost(HTTPRequest &request, HTTPResponse &response);
  void doDelete(HTTPRequest &request, HTTPResponse &response);

  void doError(HTTPRequest &request, HTTPResponse &response);

 private:
  HTTPServletStatic(const HTTPServletStatic &src);
  HTTPServletStatic &operator=(const HTTPServletStatic &src);
};

#endif