#ifndef NET_HTTP_HTTP_REQUEST_FAKE_HPP
#define NET_HTTP_HTTP_REQUEST_FAKE_HPP

#include <string>

#include "../../error/Log.hpp"
#include "../Request.hpp"
#include "../SocketFileDescriptor.hpp"

class HTTPRequestFake : public Request {
 public:
  HTTPRequestFake(SocketFileDescriptor *socketFD, Log *logger);
  ~HTTPRequestFake();

  StateOfCreation createRequest();

  bool isTheHTTPHeaderComplete(std::string _buffer);

 private:
  HTTPRequestFake(const HTTPRequestFake &src);
  HTTPRequestFake &operator=(const HTTPRequestFake &src);

  SocketFileDescriptor *_socketFD;
  std::string _buffer;
  Log *_logger;
};

#endif