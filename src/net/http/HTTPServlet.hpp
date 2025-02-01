#ifndef NET_HTTP_HTTP_SERVLET_HPP
#define NET_HTTP_HTTP_SERVLET_HPP

#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include "HTTPStatus.hpp"

class HTTPServlet {
 public:
  virtual ~HTTPServlet() = 0;

  virtual HTTPStatus::Status doGet(HTTPRequest &request,
                                   HTTPResponse &response) = 0;
  virtual HTTPStatus::Status doPost(HTTPRequest &request,
                                    HTTPResponse &response) = 0;
  virtual HTTPStatus::Status doDelete(HTTPRequest &request,
                                      HTTPResponse &response) = 0;
};

#endif