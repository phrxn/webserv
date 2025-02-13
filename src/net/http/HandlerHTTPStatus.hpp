#ifndef NET_HTTP_HANDLER_HTTP_STATUS_HPP
#define NET_HTTP_HANDLER_HTTP_STATUS_HPP

#include <string>

#include "../../start/CreateDefaultErrorPagesFactory.hpp"
#include "../../time/Time.hpp"
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include "../VirtualHostDefault.hpp"
#include "html/FillHTTPResponse.hpp"
#include "html/HTMLDocument.hpp"

class HandlerHTTPStatus {
 public:
  HandlerHTTPStatus(const VirtualHostDefault *virtualHost);
  ~HandlerHTTPStatus();
  HandlerHTTPStatus(const HandlerHTTPStatus &src);
  HandlerHTTPStatus &operator=(const HandlerHTTPStatus &src);

  void doStatusError(HTTPResponse &response, HTTPStatus::Status status);

  void doStatusFamily200(HTTPRequest &request, HTTPResponse &response,
                         HTTPStatus::Status status);

  void doStatusFamily300(HTTPResponse &response, HTTPStatus::Status status,
                         const std::string &thePathToRedirect);

  void createErrorHTTPResponse(HTTPResponse &response,
                               HTTPStatus::Status status);

 private:
  void stampTheResponse(HTTPResponse &response, HTTPStatus::Status status);

  void loadPageErrorPage(HTTPStatus::Status status);

  const VirtualHostDefault *_virtualHost;
  CreateDefaultErrorPagesFactory _createDefaultErrorPagesFactory;
  HTMLDocument *_httpDocument;
  FillHTTPResponse _fillHTTPResponse;
  Time _time;
};

#endif