#include "SocketFileDescriptor.hpp"

SocketFileDescriptor::SocketFileDescriptor(int fd)
    : FileDescriptor(fd), _closeSocketAfterProcessingResponse(false) {}

SocketFileDescriptor::~SocketFileDescriptor() {}

// deleted (this class or its heirs MUST BE UNIQUE!)
SocketFileDescriptor::SocketFileDescriptor(const SocketFileDescriptor &src)
    : FileDescriptor(src) {
  (void)src;
  *this = src;
};

// deleted (this class MUST BE UNIQUE!)
SocketFileDescriptor &SocketFileDescriptor::operator=(
    const SocketFileDescriptor &src) {
  (void)src;
  return *this;
}

std::vector<char> &SocketFileDescriptor::getInputStream() {
  return _vectorInputStream;
}

std::vector<char> &SocketFileDescriptor::getOutputStream() {
  return _vectorOutputStream;
}

// Tells whether the socket should be closed after the request response
// has been sent.
void SocketFileDescriptor::setCloseSocketAfterProcessingResponse(
    bool isToClose) {
  _closeSocketAfterProcessingResponse = isToClose;
}

// Tells whether the socket should be closed after the request response
// has been sent.
bool SocketFileDescriptor::isForCloseSocketAfterProcessingResponse() const {
  return _closeSocketAfterProcessingResponse;
}

void SocketFileDescriptor::setServerPort(int serverPort) {
  _serverPort = serverPort;
}
int SocketFileDescriptor::getServerPort() const { return _serverPort; }

void SocketFileDescriptor::setRemoteClientPort(int port) {
	_remoteClientPort = port;
}
int SocketFileDescriptor::getRemoteClientPort() const {
	return _remoteClientPort;
}
void SocketFileDescriptor::setClientIPv4(const std::string &ipv4) {
	_clientIPv4 = ipv4;
}
std::string SocketFileDescriptor::getClientIPv4() const {
	return _clientIPv4;
}