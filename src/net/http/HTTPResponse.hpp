#ifndef NET_HTTP_HTTP_RESPONSE_HPP
#define NET_HTTP_HTTP_RESPONSE_HPP

#include <map>
#include <string>

#include "../Response.hpp"
#include "../SocketFileDescriptor.hpp"
#include "HTTPStatus.hpp"

class HTTPResponse : public Response {
 public:
  const static std::string KEY_AND_VALUE_SEPARATOR;

  HTTPResponse(SocketFileDescriptor *socketFD);
  ~HTTPResponse();

  void createResponse();

  void setHTTPVersion(const std::string &httpVersion);
  void setStatus(HTTPStatus::Status status);
  HTTPStatus::Status getStatus() const;
  std::string getStatusStr() const;
  void setServer(const std::string &server);
  void setDate(const std::string &date);
  void setContentType(const std::string &contentType);
  void setContentLength(const std::string &contentLength);
  void setContentLength(std::size_t contentLength);
  void setLastModified(const std::string &lastModified);
  void setConnection(const std::string &connection);
  bool closeConnectionAfterThatResponse() const;

  void addHeader(const std::string &key, const std::string &value);

  void setBody(const std::string &body);

  std::string createResponseString();

 private:
  HTTPResponse(const HTTPResponse &src);
  HTTPResponse &operator=(const HTTPResponse &src);

  SocketFileDescriptor *_socketFD;

  std::string _httpVersion;
  std::string _statusStr;
  std::string _server;
  std::string _date;
  std::string _contentType;
  std::string _contentLength;
  std::string _lastModified;
  std::string _connection;


  HTTPStatus::Status _status;
  bool _closeConnectionAfterThatResponse;
  std::map<std::string, std::string> _mapOtherHeaders;
  std::string _body;
};

#endif