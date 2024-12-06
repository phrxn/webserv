#ifndef NET_HTTP_HTTP_SERVLET_CGI_HPP
#define NET_HTTP_HTTP_SERVLET_CGI_HPP

#include "HTTPServlet.hpp"
#include "../VirtualHost.hpp"

class HTTPServletCGI : public HTTPServlet {
 public:
  HTTPServletCGI(const VirtualHost *_virtualHost);
  ~HTTPServletCGI();

  void doGet(HTTPRequest &request, HTTPResponse &response);
  void doPost(HTTPRequest &request, HTTPResponse &response);
  void doDelete(HTTPRequest &request, HTTPResponse &response);

 private:
  HTTPServletCGI(const HTTPServletCGI &src);
  HTTPServletCGI &operator=(const HTTPServletCGI &src);

  const VirtualHost *_virtualHost;
};

#endif