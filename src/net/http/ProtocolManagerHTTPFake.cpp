#include "ProtocolManagerHTTPFake.hpp"

ProtocolManagerHTTPFake::ProtocolManagerHTTPFake(SocketFileDescriptor *socket,
                                                 Log *logger)
    : _hTTPRequestFake(socket, logger),
      _hTTPResponseFake(socket, logger),
      _socketFD(socket),
      _logger(logger) {}

ProtocolManagerHTTPFake::~ProtocolManagerHTTPFake() {}

// deleted (this class MUST BE UNIQUE!)
ProtocolManagerHTTPFake::ProtocolManagerHTTPFake(
    const ProtocolManagerHTTPFake &src)
    : _hTTPRequestFake(src._socketFD, src._logger),
      _hTTPResponseFake(src._socketFD, src._logger),
      _logger(src._logger) {
  (void)src;
}

// deleted (this class MUST BE UNIQUE!)
ProtocolManagerHTTPFake &ProtocolManagerHTTPFake::operator=(
    const ProtocolManagerHTTPFake &src) {
  (void)src;
  return *this;
}

ProtocolManager::RequestCreationStatus
ProtocolManagerHTTPFake::createRequest() {
  if (_hTTPRequestFake.createRequest() == Request::REQUEST_CREATING)
    return REQUEST_CREATING;
  return REQUEST_CREATED;
}

void ProtocolManagerHTTPFake::servlet() {}

void ProtocolManagerHTTPFake::createResponse() {
  _hTTPResponseFake.createResponse();
}

void ProtocolManagerHTTPFake::connectionHitTheTimeout() {}