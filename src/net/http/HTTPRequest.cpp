#include "HTTPRequest.hpp"

#include <iostream>
#include <vector>

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
  
  if(headerRequest() == REQUEST_CREATING){
    return REQUEST_CREATING;
  }

  return REQUEST_CREATED;
}

HTTPRequest::StateOfCreation HTTPRequest::headerRequest() {
    std::vector<char> &data = _socketFD->getInputStream();
    std::string strTmp(data.begin(), data.begin() + data.size());
    data.clear();
    _buffer += strTmp;

    if (!isTheHTTPHeaderComplete(_buffer)) {
        return HEADER_CREATING;
    }

    std::map<std::string, std::string> headers;
    std::size_t pos = 0;
    std::string line;
    while (pos < _buffer.size()) {
      line = _buffer.substr(pos, _buffer.find("\r\n", pos) - pos);
      pos += line.size() + 2; // Skip the line and the \r\n

      if (line.empty()) {
        break; // End of headers
      }

      std::size_t colonPos = line.find(":");
      if (colonPos != std::string::npos) {
          std::string key = line.substr(0, colonPos);
          std::string value = line.substr(colonPos + 2); // Skip ": "
          headers[key] = value;
      }
      else {
        colonPos = line.find(" ");
        if (colonPos != std::string::npos) {
          std::string key = "Method";
          std::string value = line.substr(0, colonPos);
          headers[key] = value;
          key = "URL";
          value = line.substr(colonPos + 1);
          headers[key] = value;
          colonPos = line.find("HTTP");
          key = "HTTP";
          value = line.substr(colonPos);
        
      }
      }
      headerValidation();
      return REQUEST_CREATED;
    }

    _header = headers; 

    _logger->log(Log::DEBUG, "HTTPRequestFake", "createRequest", _buffer, "");

    return HEADER_CREATED;
}

HTTPRequest::Status HTTPRequest::headerValidation()
{
    if (_header.find("Host") == _header.end() || _header.find("Content-Length") == _header.end() 
        || _header.find("Method") == _header.end() || _header.find("URL") == _header.end() || ){
        return HTTPStatus::BAD_REQUEST;
    }

    return HTTPStatus::OK;
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