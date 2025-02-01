#ifndef NET_HTTP_HTML_FILL_HTTP_RESPONSE_HPP
#define NET_HTTP_HTML_FILL_HTTP_RESPONSE_HPP

#include "../HTTPRequest.hpp"
#include "../HTTPResponse.hpp"
#include "HTMLDocument.hpp"

class FillHTTPResponse {
 public:
  FillHTTPResponse();
  ~FillHTTPResponse();
  FillHTTPResponse(const FillHTTPResponse &src);
  FillHTTPResponse &operator=(const FillHTTPResponse &src);

  void makeFill(HTTPResponse &response, HTMLDocument &htmlDocument);
};

#endif