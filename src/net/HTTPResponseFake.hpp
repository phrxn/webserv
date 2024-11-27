#ifndef NET_HTTP_RESPONSE_FAKE_HTTP
#define NET_HTTP_RESPONSE_FAKE_HTTP

#include "../error/Log.hpp"
#include "Response.hpp"
#include "SocketFileDescriptor.hpp"

class HTTPResponseFake : public Response {
 public:
  HTTPResponseFake(SocketFileDescriptor *socketFD, Log *logger);
  ~HTTPResponseFake();

  void createResponse();

 private:
  HTTPResponseFake(const HTTPResponseFake &src);
  HTTPResponseFake &operator=(const HTTPResponseFake &src);

  SocketFileDescriptor *_socketFD;
  Log *_logger;
};

#endif