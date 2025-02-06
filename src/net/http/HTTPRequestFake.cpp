#include "HTTPRequestFake.hpp"

#include "../SocketFileDescriptorImpl.hpp"

HTTPRequestFake::HTTPRequestFake(SocketFileDescriptor *socketFD, Log *logger)
    : HTTPRequest(socketFD, logger), _socketFD(socketFD), _logger(logger), _status(HTTPStatus::INVALID) {}

HTTPRequestFake::~HTTPRequestFake() {}

// deleted (this class MUST BE UNIQUE!)
HTTPRequestFake::HTTPRequestFake(const HTTPRequestFake &src)
    : HTTPRequest(src._socketFD, src._logger), _logger(src._logger) {
  (void)src;
}

// deleted (this class MUST BE UNIQUE!)
HTTPRequestFake &HTTPRequestFake::operator=(const HTTPRequestFake &src) {
  (void)src;
  return *this;
}


#include <sstream>
HTTPRequestFake::StateOfCreation HTTPRequestFake::createRequest() {
  std::vector<char> &date = _socketFD->getInputStream();

  std::string strTmp(date.begin(), date.begin() + date.size());

  date.clear();

  _buffer += strTmp;

  if (!isTheHTTPHeaderComplete(_buffer)) return REQUEST_CREATING;

  std::stringstream ss(_buffer);

  ss >> _method;
  ss >> _url;

  _status = HTTPStatus::OK;

  _logger->log(Log::DEBUG, "HTTPRequestFake", "createRequest", _buffer, "");

  return REQUEST_CREATED;
}

bool HTTPRequestFake::isTheHTTPHeaderComplete(std::string _buffer) {
  if (_buffer.find("\r\n\r\n") != std::string::npos) return true;
  return false;
}

HTTPMethods::Method HTTPRequestFake::getMethod() const{
	HTTPMethods convert;
	return convert.getStringToMethod(_method);
}

std::string HTTPRequestFake::getURLStr() const{
	return _url;
}

URL HTTPRequestFake::getURL() const{
	return _url;
}

HTTPStatus::Status HTTPRequestFake::getStatus() const{
	return _status;
}