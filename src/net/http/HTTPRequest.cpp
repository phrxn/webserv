#include "HTTPRequest.hpp"
#include "HTTPMethods.hpp"
#include <iostream>
#include <vector>

#include "../../config/ProgramConfiguration.hpp"

HTTPRequest::HTTPRequest(SocketFileDescriptor *socketFD, Log *logger)
: _HTTPTool(logger), _countBodySizeWhileReadRequest(0), _wasTheHeaderPartFound(false)
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

#include <iostream>
HTTPRequest::StateOfCreation HTTPRequest::createRequest() {
	std::vector<char> &data = _socketFD->getInputStream();
	std::string strTmp(data.begin(), data.begin() + data.size());
	data.clear();
	_buffer += strTmp;

	// CHECA PELO PAYLOAD! SE FOR MAIOR QUE O PERMITIDO, RETORNA QUE A REQUEST FOI CRIADA
	// MAS COMO PAYLOAD GRANDE DEMAIS
	if (_HTTPTool.isTheHTTPHeaderComplete(_buffer) || _wasTheHeaderPartFound){
		if (_wasTheHeaderPartFound){
			_countBodySizeWhileReadRequest += strTmp.size();
		}else{
			_countBodySizeWhileReadRequest = _buffer.size() - (_buffer.find("\r\n\r\n") + 4);
			_wasTheHeaderPartFound = true;
		}
		if (_countBodySizeWhileReadRequest > ProgramConfiguration::getInstance().getMaxRequestSizeInBytes()) {
			_status = HTTPStatus::REQUEST_ENTITY_TOO_LARGE;
			return REQUEST_CREATED;
		}
	}

	if (_HTTPTool.isTheHTTPHeaderComplete(_buffer) || _HTTPTool.isBodyComplete(_buffer) || _HTTPTool.isChunked()) {
		//FAZER  IF PARA O HEADER
		if(_HTTPTool.isTheHTTPHeaderComplete(_buffer) && !_HTTPTool.isParsed()){
			_HTTPTool.parserHeader(_buffer);
			_buffer = _buffer.substr(_buffer.find("\r\n\r\n") + 4);
			_logger->log(Log::DEBUG, "HTTPRequest", "createRequest", "the status *1", _HTTPTool.getStatus());
		}
		if(_HTTPTool.isChunked()){
			_logger->log(Log::DEBUG, "HTTPRequest", "createRequest", "the status *2", _HTTPTool.getStatus());
			_HTTPTool.parseChunkedBody(_buffer);
			if(_HTTPTool.getBody().size() > 0 && _HTTPTool.isChunkedEnd(_buffer)){
				_logger->log(Log::DEBUG, "HTTPRequest", "createRequest", "BODY CHUNKED", _HTTPTool.getBody());
				return REQUEST_CREATED;
			}
			else
				return REQUEST_CREATING;
		}
		if(_HTTPTool.HasBody()){
			_logger->log(Log::DEBUG, "HTTPRequest", "createRequest", "BUFFER", _buffer);
			_HTTPTool.setBody(_buffer);
			_logger->log(Log::DEBUG, "HTTPRequest", "createRequest", "the body", _HTTPTool.getBody());
		}
		if (_HTTPTool.isBodyComplete(_buffer)){
			_logger->log(Log::DEBUG, "HTTPRequest", "createRequest", "the status *3", _HTTPTool.getStatus());
			return REQUEST_CREATED;
		}else{
			return REQUEST_CREATING;
		}
	}
	_logger->log(Log::DEBUG, "HTTPRequest", "createRequest", "", _buffer);
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
	std::string host = _HTTPTool.getHeader("Host");
	if (host.empty()) {
		return "";
	}
	size_t pos = host.find(':');

	//remove port from host if it exists
    if (pos != std::string::npos) {
        return host.substr(0, pos);
    }
    return host;
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

URL HTTPRequest::getURL(){
	return URL(getURLStr());
}

std::string HTTPRequest::getContentType() {
	return _HTTPTool.getHeader("Content-Type");
}

std::string HTTPRequest::getContentLength() {
	return _HTTPTool.getHeader("Content-Length");
}

std::string HTTPRequest::getCookie() {
	return _HTTPTool.getHeader("Cookie");
}

std::string HTTPRequest::getBody(){
	return _HTTPTool.getBody();
}