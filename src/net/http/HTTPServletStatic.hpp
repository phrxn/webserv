#ifndef NET_HTTP_HTTP_SERVLET_STATIC_HPP
#define NET_HTTP_HTTP_SERVLET_STATIC_HPP

#include "../VirtualHostDefault.hpp"
#include "HTTPServlet.hpp"
#include "StaticPagesPhysicalPathChecker.hpp"
#include "html/FillHTTPResponse.hpp"
#include "html/HTMLDocument.hpp"

class HTTPServletStatic : public HTTPServlet {
 public:
  HTTPServletStatic(const std::string &physicalPathToResource,
                    const std::string &urlPathToDir, bool canListDirectory);
  ~HTTPServletStatic();

  HTTPStatus::Status doGet(HTTPRequest &request, HTTPResponse &response);
  HTTPStatus::Status doPost(HTTPRequest &request, HTTPResponse &response);
  HTTPStatus::Status doDelete(HTTPRequest &request, HTTPResponse &response);

 private:
  HTTPServletStatic(const HTTPServletStatic &src);
  HTTPServletStatic &operator=(const HTTPServletStatic &src);

  std::string _physicalPathToResource;
  std::string _urlPathToDir;
  bool _canListDirectory;
  StaticPagesPhysicalPathChecker *_physicalPathChecker;
  HTMLDocument *_htmlDocument;
  FillHTTPResponse _fillHTTPResponse;
};

#endif