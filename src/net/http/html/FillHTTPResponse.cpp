#include "FillHTTPResponse.hpp"

FillHTTPResponse::FillHTTPResponse() {}

FillHTTPResponse::~FillHTTPResponse() {}

FillHTTPResponse::FillHTTPResponse(const FillHTTPResponse &src) { (void)src; }

FillHTTPResponse &FillHTTPResponse::operator=(const FillHTTPResponse &src) {
  (void)src;
  return *this;
}

void FillHTTPResponse::makeFill(HTTPResponse &response, HTMLDocument &htmlDocument){

  response.setContentLength(htmlDocument.getSize());
  response.setContentType(htmlDocument.getMimeType());
  response.setLastModified(htmlDocument.getLastModified());
  response.setBody(htmlDocument.getData());
}