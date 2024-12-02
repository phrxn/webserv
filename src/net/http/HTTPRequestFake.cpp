#include "HTTPRequestFake.hpp"

#include <iostream>

#include "../SocketFileDescriptorImpl.hpp"

HTTPRequestFake::HTTPRequestFake(SocketFileDescriptor *socketFD, Log *logger)
    : _socketFD(socketFD), _logger(logger) {}

HTTPRequestFake::~HTTPRequestFake() {}

// deleted (this class MUST BE UNIQUE!)
HTTPRequestFake::HTTPRequestFake(const HTTPRequestFake &src)
    : _logger(src._logger) {
  (void)src;
}

// deleted (this class MUST BE UNIQUE!)
HTTPRequestFake &HTTPRequestFake::operator=(const HTTPRequestFake &src) {
  (void)src;
  return *this;
}

HTTPRequestFake::StateOfCreation HTTPRequestFake::createRequest() {
  std::vector<char> &date = _socketFD->getInputStream();

  std::string strTmp(date.begin(), date.begin() + date.size());

  date.clear();

  _buffer += strTmp;

  if (!isTheHTTPHeaderComplete(_buffer)) return REQUEST_CREATING;

  _logger->log(Log::DEBUG, "HTTPRequestFake", "createRequest", _buffer, "");

  return REQUEST_CREATED;
}

bool HTTPRequestFake::isTheHTTPHeaderComplete(std::string _buffer){
	if (_buffer.find("\r\n\r\n") != std::string::npos)
		return true;
	return false;
}