#ifndef NET_HTTP_HTTP_REQUEST_HPP
#define NET_HTTP_HTTP_REQUEST_HPP

#include <string>

#include "../Request.hpp"
#include "../SocketFileDescriptor.hpp"

class HTTPRequest : public Request {
 public:
  HTTPRequest(SocketFileDescriptor *socketFD);
  ~HTTPRequest();

  StateOfCreation createRequest();

 private:
  HTTPRequest(const HTTPRequest &src);
  HTTPRequest &operator=(const HTTPRequest &src);

  SocketFileDescriptor *_socketFD;
  std::string _buffer;
};

#endif