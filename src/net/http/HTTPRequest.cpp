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
	std::vector<char> &data = _socketFD->getInputStream();
	std::string strTmp(data.begin(), data.begin() + data.size());
	data.clear();
	_buffer += strTmp;

	if (_HTTPTool.isTheHTTPHeaderComplete(_buffer) || _HTTPTool.isBodyComplete(_buffer) || _HTTPTool.isChunked()) {
		//FAZER  IF PARA O HEADER 
		if(_HTTPTool.isTheHTTPHeaderComplete(_buffer) && !_HTTPTool.isParsed()){
			_HTTPTool.parserHeader(_buffer);
			_buffer = _buffer.substr(_buffer.find("\r\n\r\n") + 4);
		}
		if(_HTTPTool.isChunked()){
			_buffer = _HTTPTool.parseChunkedBody(_buffer);
			if(_HTTPTool.isChunkedEnd(_buffer)){
				return REQUEST_CREATED;
			}
			else
				return REQUEST_CREATING;
		}
		_HTTPTool.setBody(_buffer);
		return REQUEST_CREATED;
	}
	_logger->log(Log::DEBUG, "HTTPRequest", "createRequest", _buffer, "");
	return REQUEST_CREATING;
}



HTTPStatus::Status HTTPRequest::getStatus() {
	return _HTTPTool.getStatus();
}

HTTPMethods::Method HTTPRequest::getMethod(const std::string method){
	return _HTTPTool.getHeader(method);
}

std::string HTTPRequest::getURL(){
	return _HTTPTool.getHeader("URL");
}

std::string HTTPRequest::getHost(){
	return _HTTPTool.getHeader("Host");
}

std::string HTTPRequest::isToKeepTheConnection(){
	return _HTTPTool.getHeader("Connection");
}

int HTTPRequest::getPort(){
	return _socketFD->getServerPort();
}
