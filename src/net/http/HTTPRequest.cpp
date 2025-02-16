#include "HTTPRequest.hpp"
#include "HTTPMethods.hpp"
#include <iostream>
#include <vector>

HTTPRequest::HTTPRequest(SocketFileDescriptor *socketFD, Log *logger)
: _HTTPTool(logger)
{
	_socketFD = socketFD;
	_logger = logger;
}

HTTPRequest::~HTTPRequest() {}

HTTPRequest::HTTPRequest(Log *logger) : _HTTPTool(logger) {}

// deleted (this class MUST BE UNIQUE!)
HTTPRequest::HTTPRequest(const HTTPRequest &src) : _HTTPTool(src._logger) { (void)src; }

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
			_logger->log(Log::DEBUG, "HTTPRequest", "createRequest", "the status *1", _HTTPTool.getStatus());
		}
		if(_HTTPTool.isChunked()){
			_buffer = _HTTPTool.parseChunkedBody(_buffer);
			if(_HTTPTool.isChunkedEnd(_buffer)){
				_logger->log(Log::DEBUG, "HTTPRequest", "createRequest", "the status *2", _HTTPTool.getStatus());
				return REQUEST_CREATED;
			}
			else
				return REQUEST_CREATING;
		}
		if(!_HTTPTool.HasBody()){
			_HTTPTool.setBody(_buffer);
		}
		_logger->log(Log::DEBUG, "HTTPRequest", "createRequest", "the status *3", _HTTPTool.getStatus());
		return REQUEST_CREATED;
	}
	_logger->log(Log::DEBUG, "HTTPRequest", "createRequest", _buffer, "");
	_logger->log(Log::DEBUG, "HTTPRequest", "createRequest", "the status when request is created *4", _HTTPTool.getStatus());
	return REQUEST_CREATING;
}

HTTPStatus::Status HTTPRequest::getStatus(){
	return _HTTPTool.getStatus();
}

HTTPMethods::Method HTTPRequest::getMethod(){
	return _method.getStringToMethod( _HTTPTool.getHeader("Method"));
}

std::string HTTPRequest::getURLStr(){
	return _HTTPTool.getHeader("URL");
}

std::string HTTPRequest::getHost(){
	return _HTTPTool.getHeader("Host");
}

std::string HTTPRequest::isToKeepTheConnection(){
	return _HTTPTool.getHeader("Connection");
}


//-----------------------------------------------


int HTTPRequest::getPort() const{
	return _socketFD->getServerPort();
}

std::string HTTPRequest::getClientAddressIPv4() const{
	return _socketFD->getClientIPv4();
}

URL HTTPRequest::getURL() const {
	return URL();
}

std::string HTTPRequest::getContentType() const {
	return "";
}

std::string HTTPRequest::getContentLength() const {
	return "";
}

std::string HTTPRequest::getCookie() const{
	return "";
}

std::string HTTPRequest::getBody(){
	return _HTTPTool.getBody();
}