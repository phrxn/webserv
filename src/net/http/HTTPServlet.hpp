#ifndef NET_HTTP_HTTP_SERVLET_HPP
#define NET_HTTP_HTTP_SERVLET_HPP

#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"

class HTTPServlet {
 public:
  virtual ~HTTPServlet() = 0;

  virtual void doGet(HTTPRequest &request, HTTPResponse &response) = 0;
  virtual void doPost(HTTPRequest &request, HTTPResponse &response) = 0;
  virtual void doDelete(HTTPRequest &request, HTTPResponse &response) = 0;

  virtual void doError(HTTPRequest &request, HTTPResponse &response) = 0;
};

#endif