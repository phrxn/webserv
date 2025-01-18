#ifndef NET_HTTP_HTTP_REQUEST_HPP
#define NET_HTTP_HTTP_REQUEST_HPP

#include <string>

#include "../Request.hpp"
#include "../../error/Log.hpp"
#include "../SocketFileDescriptor.hpp"
#include "HTTPStatus.hpp"
#include "HTTPMethods.hpp"

class HTTPRequest : public Request {
 public:
  HTTPRequest(SocketFileDescriptor *socketFD, log *logger);
  ~HTTPRequest();

  StateOfCreation createRequest();

  std::string getHost();

  HTTPMethods::Method getMethod();

  std::string getURL();

  HTTPStatus::Status getStatus();

  bool isTheHTTPHeaderComplete(std::string _buffer);

 private:
  HTTPRequest(const HTTPRequest &src);
  HTTPRequest &operator=(const HTTPRequest &src);

  SocketFileDescriptor *_socketFD;
  std::string _buffer;
  log *_logger
};

#endif