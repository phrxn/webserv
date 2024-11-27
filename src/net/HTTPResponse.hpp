#ifndef NET_HTTP_RESPONSE_HPP
#define NET_HTTP_RESPONSE_HPP

#include "Response.hpp"
#include "SocketFileDescriptor.hpp"

class HTTPResponse : public Response {
public:
  HTTPResponse(SocketFileDescriptor *socketFD);
  ~HTTPResponse();


  void createResponse();

 private:
  HTTPResponse(const HTTPResponse &src);
  HTTPResponse &operator=(const HTTPResponse &src);

  SocketFileDescriptor *_socketFD;

};

#endif