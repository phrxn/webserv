#ifndef NET_HTTP_HTTP_RESPONSE_FAKE_HPP
#define NET_HTTP_HTTP_RESPONSE_FAKE_HPP

#include "../../error/Log.hpp"
#include "HTTPResponse.hpp"
#include "../SocketFileDescriptor.hpp"

class HTTPResponseFake : public HTTPResponse {
 public:
  HTTPResponseFake(SocketFileDescriptor *socketFD, Log *logger);
  ~HTTPResponseFake();

 private:
  HTTPResponseFake(const HTTPResponseFake &src);
  HTTPResponseFake &operator=(const HTTPResponseFake &src);

  Log *_logger;
};

#endif