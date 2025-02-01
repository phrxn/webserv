#include "HTTPResponseFake.hpp"

#include <string>

HTTPResponseFake::HTTPResponseFake(SocketFileDescriptor *socketFD, Log *logger)
    : HTTPResponse(socketFD), _logger(logger) {}

HTTPResponseFake::~HTTPResponseFake() {}

// deleted (this class MUST BE UNIQUE!)
HTTPResponseFake::HTTPResponseFake(const HTTPResponseFake &src)
    :  HTTPResponse(NULL),  _logger(src._logger) {
  (void)src;
}

// deleted (this class MUST BE UNIQUE!)
HTTPResponseFake &HTTPResponseFake::operator=(const HTTPResponseFake &src) {
  (void)src;
  return *this;
}