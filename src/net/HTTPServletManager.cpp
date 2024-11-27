#include "HTTPServletManager.hpp"

#include "HTTPServletStatic.hpp"

HTTPServletManager::HTTPServletManager(SocketFileDescriptor *socketFD)
    : _hTTPServlet(new HTTPServletStatic) {
	(void)socketFD;
}

HTTPServletManager::~HTTPServletManager() {
	if (_hTTPServlet) delete _hTTPServlet;
}

// deleted (this class MUST BE UNIQUE!)
HTTPServletManager::HTTPServletManager(const HTTPServletManager &src){
	(void)src;
}

// deleted (this class MUST BE UNIQUE!)
HTTPServletManager &HTTPServletManager::operator=(const HTTPServletManager &src){
  (void)src;
  return *this;
}

void HTTPServletManager::doService(HTTPRequest &request,
                                   HTTPResponse &response) {
	(void)request;
	(void)response;
}

void HTTPServletManager::doError(int CodeError, HTTPResponse &response) {
	(void)CodeError;
	(void)response;
}