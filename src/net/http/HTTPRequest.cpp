#include "HTTPRequest.hpp"

#include <iostream>

HTTPRequest::HTTPRequest(SocketFileDescriptor *socketFD, log *logger)
{
  _socketFD = socketFD;
  (void)_header;
  (void)_body;
  _logger = logger;
}

HTTPRequest::~HTTPRequest() {}

// deleted (this class MUST BE UNIQUE!)
HTTPRequest::HTTPRequest(const HTTPRequest &src) { (void)src; }

// deleted (this class MUST BE UNIQUE!)
HTTPRequest &HTTPRequest::operator=(const HTTPRequest &src) {
  (void)src;
  return *this;
}

HTTPRequest::StateOfCreation HTTPRequest::createRequest() {
  std::vector<char> &date = _socketFD->getInputStream(); //pegando o input do socket

  std::string strTmp(date.begin(), date.begin() + date.size());// transformando ele em string

  date.clear();

  buffer += strTmp;
  if (!isTheHTTPHeaderComplete(_buffer)) { 

    return REQUEST_CREATING;
  }

  return REQUEST_CREATED;
}

std::string HTTPRequest::getHost() { return ""; }

HTTPMethods::Method HTTPRequest::getMethod(){
	return HTTPMethods::GET;
}

std::string HTTPRequest::getURL(){
	return "";
}

HTTPStatus::Status HTTPRequest::getStatus(){
	return HTTPStatus::OK;
}

bool HTTPRequestFake::isTheHTTPHeaderComplete(std::string _buffer){
	if (_buffer.find("\r\n\r\n") != std::string::npos)
		return true;
	return false;