#ifndef NET_HTTP_HTTP_RESPONSE_HPP
#define NET_HTTP_HTTP_RESPONSE_HPP

#include "../Response.hpp"
#include "../SocketFileDescriptor.hpp"
#include "HTTPStatus.hpp"

class HTTPResponse : public Response {
 public:
  HTTPResponse(SocketFileDescriptor *socketFD);
  ~HTTPResponse();

  void createResponse();

  HTTPStatus getStatus();
  void setStatus(HTTPStatus status);

 private:
  HTTPResponse(const HTTPResponse &src);
  HTTPResponse &operator=(const HTTPResponse &src);

  SocketFileDescriptor *_socketFD;
};

#endif