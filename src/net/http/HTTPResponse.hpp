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
  void setHeaders(const std::map<std::string, std::vector<std::string> > &headers);

  bool setServer(const std::string &server);
  bool setDate(const std::string &date);
  bool setContentType(const std::string &contentType);
  bool setContentLength(const std::string &contentLength);
  bool setContentLength(std::size_t contentLength);
  bool setLastModified(const std::string &lastModified);
  bool setConnection(const std::string &connection);
  bool closeConnectionAfterThatResponse() const;

  bool addHeader(const std::string &key, const std::string &value);

  void setBody(const std::string &body);

  void setItACGIResponse(bool isItACGIResponse);

  std::string createResponseString() const;

 private:
  HTTPResponse(const HTTPResponse &src);
  HTTPResponse &operator=(const HTTPResponse &src);

  bool _addHeader(const std::string &key, const std::string &value);

  SocketFileDescriptor *_socketFD;

  std::string _httpVersion;
  std::string _statusStr;

  HTTPStatus::Status _status;
  bool _closeConnectionAfterThatResponse;
  std::map<std::string, std::string> _mapOtherHeaders;
  std::string _body;
  bool _isItACGIResponse;

  std::map<std::string, std::vector<std::string> > _headers;
};

std::ostream &operator<<(std::ostream &os, const HTTPResponse &response);

#endif