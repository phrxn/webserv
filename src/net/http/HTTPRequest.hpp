#ifndef NET_HTTP_HTTP_REQUEST_HPP
#define NET_HTTP_HTTP_REQUEST_HPP

#include <map>
#include <string>

#include "../../error/Log.hpp"
#include "../Request.hpp"
#include "../SocketFileDescriptor.hpp"
#include "../URL.hpp"
#include "HTTPMethods.hpp"
#include "HTTPStatus.hpp"
#include "HTTPRequestTool.hpp"
#include "../URL.hpp"

class HTTPRequest : public Request {
 private:
  HTTPRequest(const HTTPRequest &src);
  HTTPRequest &operator=(const HTTPRequest &src);
  HTTPRequest(Log *logger);

  StateOfCreation headerRequest();

  SocketFileDescriptor *_socketFD;
  std::string _buffer;
  HTTPStatus::Status _status;
  HTTPRequestTool _HTTPTool;
  Log *_logger;
  HTTPMethods _method;

 public:
  HTTPRequest(SocketFileDescriptor *socketFD, Log *logger);
  virtual ~HTTPRequest();

  StateOfCreation createRequest();

  virtual HTTPStatus::Status getStatus();

  virtual HTTPMethods::Method getMethod();

  virtual std::string getURLStr();

  virtual std::string getHost();

  virtual std::string isToKeepTheConnection();






  virtual int getPort() const;

  virtual std::string getClientAddressIPv4() const;

  virtual URL getURL() const;

  virtual std::string getContentType() const;

  virtual std::string getContentLength() const;

  virtual std::string getCookie() const;

  virtual std::string getBody();
};

#endif
