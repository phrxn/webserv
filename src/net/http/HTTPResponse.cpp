#include "HTTPResponse.hpp"

HTTPResponse::HTTPResponse(SocketFileDescriptor *socketFD) : _socketFD(socketFD) {
	(void)_socketFD;
}

HTTPResponse::~HTTPResponse() {}

// deleted (this class MUST BE UNIQUE!)
HTTPResponse::HTTPResponse(const HTTPResponse &src) {
	(void)src;
}
// deleted (this class MUST BE UNIQUE!)
HTTPResponse &HTTPResponse::operator=(const HTTPResponse &src) {
	(void)src;
	return *this;
}

void HTTPResponse::createResponse() {

}

HTTPStatus HTTPResponse::getStatus(){
	return OK;
}

void HTTPResponse::setStatus(HTTPStatus status){
	(void)status;
}