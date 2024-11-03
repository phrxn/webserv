#include "SocketFileDescriptor.hpp"

SocketFileDescriptor::SocketFileDescriptor(int fd)
    : FileDescriptor(fd), _closeSocketAfterProcessingResponse(false) {}

SocketFileDescriptor::SocketFileDescriptor(int fd, const Address &address)
    : FileDescriptor(fd),
      _address(address),
      _closeSocketAfterProcessingResponse(false) {}

SocketFileDescriptor::SocketFileDescriptor(const SocketFileDescriptor &src)
    : FileDescriptor(src) {
  (void)src;
  *this = src;
};

SocketFileDescriptor::~SocketFileDescriptor() {}

// private
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
bool SocketFileDescriptor::isForCloseSocketAfterProcessingResponse() {
  return _closeSocketAfterProcessingResponse;
}