#ifndef NET_HTTP_HTTP_REQUEST_HPP
#define NET_HTTP_HTTP_REQUEST_HPP

#include <string>

#include "../Request.hpp"
#include "../SocketFileDescriptor.hpp"
#include "../URL.hpp"
#include "HTTPStatus.hpp"
#include "HTTPMethods.hpp"

class HTTPRequest : public Request {
 public:
  HTTPRequest(SocketFileDescriptor *socketFD);
  ~HTTPRequest();

  StateOfCreation createRequest();

  std::string getHost() const;

  HTTPMethods::Method getMethod() const;

  HTTPStatus::Status getStatus() const;

  std::string getContentLength() const;

  std::string getContentType() const;

  URL getURL() const;

 private:
  HTTPRequest(const HTTPRequest &src);
  HTTPRequest &operator=(const HTTPRequest &src);

  SocketFileDescriptor *_socketFD;
  std::string _buffer;
  URL _url;
};

#endif