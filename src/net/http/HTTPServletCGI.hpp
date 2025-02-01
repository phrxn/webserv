#ifndef NET_HTTP_HTTP_SERVLET_CGI_HPP
#define NET_HTTP_HTTP_SERVLET_CGI_HPP

#include "HTTPServlet.hpp"
#include "../VirtualHostDefault.hpp"

class HTTPServletCGI : public HTTPServlet {
 public:
  HTTPServletCGI(const VirtualHostDefault virtualHost);
  ~HTTPServletCGI();

  HTTPStatus::Status doGet(HTTPRequest &request, HTTPResponse &response);
  HTTPStatus::Status doPost(HTTPRequest &request, HTTPResponse &response);
  HTTPStatus::Status doDelete(HTTPRequest &request, HTTPResponse &response);

 private:
  HTTPServletCGI(const HTTPServletCGI &src);
  HTTPServletCGI &operator=(const HTTPServletCGI &src);

  const VirtualHostDefault _virtualHost;
};

#endif