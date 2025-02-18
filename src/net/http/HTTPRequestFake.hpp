#ifndef NET_HTTP_HTTP_REQUEST_FAKE_HPP
#define NET_HTTP_HTTP_REQUEST_FAKE_HPP

#include <string>

#include "../../error/Log.hpp"
#include "HTTPRequest.hpp"
#include "../SocketFileDescriptor.hpp"

class HTTPRequestFake : public HTTPRequest {
 public:
  HTTPRequestFake(SocketFileDescriptor *socketFD, Log *logger);
  ~HTTPRequestFake();

  StateOfCreation createRequest();

  std::string getHost() const;

  bool isTheHTTPHeaderComplete(std::string _buffer);

  HTTPMethods::Method getMethod() const;

  std::string getURLStr() const;

  URL getURL() const;

  HTTPStatus::Status getStatus() const;

  std::string getBody() const;

 private:
  HTTPRequestFake(const HTTPRequestFake &src);
  HTTPRequestFake &operator=(const HTTPRequestFake &src);

  SocketFileDescriptor *_socketFD;
  std::string _buffer;
  Log *_logger;

  std::string _method;
  std::string _url;
  HTTPStatus::Status _status;
  std::string _host;


};

#endif