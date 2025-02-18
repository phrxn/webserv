#ifndef NET_HTTP_HTTP_SERVLET_CGI_HPP
#define NET_HTTP_HTTP_SERVLET_CGI_HPP

#include "../VirtualHostDefault.hpp"
#include "HTTPServlet.hpp"
#include "PhysicalPathChecker.hpp"
#include "html/FillHTTPResponse.hpp"
#include "html/HTMLDocument.hpp"

class CGIHTTPServlet : public HTTPServlet {
 public:
  CGIHTTPServlet(const VirtualHost *virtualHost, const URL &url);
  ~CGIHTTPServlet();

  HTTPStatus::Status doGet(HTTPRequest &request, HTTPResponse &response);
  HTTPStatus::Status doPost(HTTPRequest &request, HTTPResponse &response);
  HTTPStatus::Status doDelete(HTTPRequest &request, HTTPResponse &response);
  HTTPStatus::Status makePage(HTTPRequest &request, HTTPResponse &response);

 private:
  CGIHTTPServlet(const CGIHTTPServlet &src);
  CGIHTTPServlet &operator=(const CGIHTTPServlet &src);

  std::string _physicalPathToResource;
  std::string _rootVirtualHostLocation;
  PhysicalPathChecker *_physicalPathChecker;
  HTMLDocument *_htmlDocument;
  FillHTTPResponse _fillHTTPResponse;
};

#endif