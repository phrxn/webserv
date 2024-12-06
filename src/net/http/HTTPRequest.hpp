#ifndef NET_HTTP_HTTP_REQUEST_HPP
#define NET_HTTP_HTTP_REQUEST_HPP

#include <string>

#include "../Request.hpp"
#include "../SocketFileDescriptor.hpp"
#include "HTTPStatus.hpp"
#include "HTTPv1_1_Methods.hpp"

class HTTPRequest : public Request {
 public:
  HTTPRequest(SocketFileDescriptor *socketFD);
  ~HTTPRequest();

  StateOfCreation createRequest();

  std::string getHost();

  HTTPv1_1_Methods getMethod();

  std::string getURL();

  HTTPStatus getStatus();

 private:
  HTTPRequest(const HTTPRequest &src);
  HTTPRequest &operator=(const HTTPRequest &src);

  SocketFileDescriptor *_socketFD;
  std::string _buffer;
};

#endif