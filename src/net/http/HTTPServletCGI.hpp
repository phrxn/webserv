#ifndef NET_HTTP_HTTP_SERVLET_CGI_HPP
#define NET_HTTP_HTTP_SERVLET_CGI_HPP

#include "../VirtualHostDefault.hpp"
#include "HTTPServlet.hpp"
#include "PhysicalPathChecker.hpp"
#include "html/FillHTTPResponse.hpp"
#include "html/HTMLDocument.hpp"

class HTTPServletCGI : public HTTPServlet {
 public:
  HTTPServletCGI(const std::string &physicalPathToResource, const std::string &rootVirtualHostLocation);
  ~HTTPServletCGI();

  HTTPStatus::Status doGet(HTTPRequest &request, HTTPResponse &response);
  HTTPStatus::Status doPost(HTTPRequest &request, HTTPResponse &response);
  HTTPStatus::Status doDelete(HTTPRequest &request, HTTPResponse &response);
  HTTPStatus::Status makePage(HTTPRequest &request, HTTPResponse &response);

 private:
  HTTPServletCGI(const HTTPServletCGI &src);
  HTTPServletCGI &operator=(const HTTPServletCGI &src);

  std::string _physicalPathToResource;
  std::string _rootVirtualHostLocation;
  PhysicalPathChecker *_physicalPathChecker;
  HTMLDocument *_htmlDocument;
  FillHTTPResponse _fillHTTPResponse;
};

#endif