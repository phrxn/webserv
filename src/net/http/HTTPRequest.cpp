#include "HTTPRequest.hpp"

#include <iostream>
#include <vector>

HTTPRequest::HTTPRequest(SocketFileDescriptor *socketFD, Log *logger)
{
	_socketFD = socketFD;
	_logger = logger;
}

HTTPRequest::~HTTPRequest() {}

HTTPRequest::HTTPRequest() {}

// deleted (this class MUST BE UNIQUE!)
HTTPRequest::HTTPRequest(const HTTPRequest &src) { (void)src; }

// deleted (this class MUST BE UNIQUE!)
HTTPRequest &HTTPRequest::operator=(const HTTPRequest &src) {
	(void)src;
	return *this;
}

HTTPRequest::StateOfCreation HTTPRequest::createRequest() {

	if(headerRequest() == REQUEST_CREATED){
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
		return REQUEST_CREATING;
	}
	_HTTPTool.parserHeader(_buffer);

	_logger->log(Log::DEBUG, "HTTPRequest", "createRequest", _buffer, "");
	return REQUEST_CREATED;
}

// void HTTPRequest::headerValidation()
// {
// 	HTTPMethods httpMethods;

// 	if (_header.find("Host") == _header.end() || _header.find("Method") == _header.end()
// 		|| _header.find("URL") == _header.end() || _header.find("HTTP-Version") == _header.end()) {

// 		_status = HTTPStatus::BAD_REQUEST;
// 	}
// 	else if (httpMethods.getStringToMethod(_header["Method"]) == HTTPMethods::INVALID) {
// 		_status = HTTPStatus::BAD_REQUEST;
// 	}
// 	else if (_header["HTTP-Version"] != "HTTP/1.1") {
// 		_status = HTTPStatus::BAD_REQUEST;
// 	}
// 	else
// 		_status = HTTPStatus::OK;
// }

// HTTPMethods::Method HTTPRequest::getAnythingFromHeader(const std::string &key){
// 	HTTPMethods httpMethods;

// 	return httpMethods.getStringToMethod(_header[key]);
// }

HTTPStatus::Status HTTPRequest::getStatus() const{
	return _status;
}

bool HTTPRequest::isTheHTTPHeaderComplete(std::string _buffer){
	if (_buffer.find("\r\n\r\n") != std::string::npos)
		return true;
	return false;
}


std::string HTTPRequest::getHost() const{
	return "";
}

HTTPMethods::Method HTTPRequest::getMethod() const{
	return HTTPMethods::GET;
}

std::string HTTPRequest::getURLStr() const{
    return "";
}

URL HTTPRequest::getURL() const {
	return URL();
}

HTTPMethods::Method HTTPRequest::getAnythingFromHeader(const std::string &key){
	(void)key;
	return HTTPMethods::GET;
}

int HTTPRequest::getPort() const{
	return _socketFD->getServerPort();
}

std::string HTTPRequest::isToKeepTheConnection() const {
	return "";
}

std::string HTTPRequest::getContentType() const {
	return "";
}

std::string HTTPRequest::getContentLength() const {
	return "";
}

std::string HTTPRequest::getClientAddressIPv4() const{
	return _socketFD->getClientIPv4();
}

std::string HTTPRequest::getCookie() const{
	return "";
}