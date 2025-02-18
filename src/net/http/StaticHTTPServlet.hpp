#ifndef NET_HTTP_HTTP_SERVLET_STATIC_HPP
#define NET_HTTP_HTTP_SERVLET_STATIC_HPP

#include "../VirtualHostDefault.hpp"
#include "../../config/ProgramConfiguration.hpp"
#include "HTTPServlet.hpp"
#include "StaticPagesPhysicalPathChecker.hpp"
#include "html/FillHTTPResponse.hpp"
#include "html/HTMLDocument.hpp"

class StaticHTTPServlet : public HTTPServlet {
 public:
  StaticHTTPServlet(const VirtualHost *virtualHost, const URL &url);
  ~StaticHTTPServlet();

  HTTPStatus::Status doGet(HTTPRequest &request, HTTPResponse &response);
  HTTPStatus::Status doPost(HTTPRequest &request, HTTPResponse &response);
  HTTPStatus::Status doDelete(HTTPRequest &request, HTTPResponse &response);

  bool absolutePathEndsWithSlash(const std::string &absolutePathToResource);

 private:
  StaticHTTPServlet(const StaticHTTPServlet &src);
  StaticHTTPServlet &operator=(const StaticHTTPServlet &src);

  const VirtualHost *_virtualHost;
  const URL &_url;
  std::string _physicalPathToResource;
  std::string _urlPathToDir;
  bool _canListDirectory;
  StaticPagesPhysicalPathChecker *_physicalPathChecker;
  HTMLDocument *_htmlDocument;
  FillHTTPResponse _fillHTTPResponse;
  ProgramConfiguration _programConfiguration;

};

#endif