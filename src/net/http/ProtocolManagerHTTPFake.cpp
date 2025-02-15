#include "ProtocolManagerHTTPFake.hpp"

ProtocolManagerHTTPFake::ProtocolManagerHTTPFake(Log *logger, SocketFileDescriptor *socket)
    : _logger(logger),
	  _hTTPRequestFake(socket, logger),
	  _hTTPResponseFake(socket, logger),
	  _hTTPServletManager(socket, logger),
      _socketFD(socket) {}

ProtocolManagerHTTPFake::~ProtocolManagerHTTPFake() {}

// deleted (this class MUST BE UNIQUE!)
ProtocolManagerHTTPFake::ProtocolManagerHTTPFake(
    const ProtocolManagerHTTPFake &src)
    : _logger(src._logger),
      _hTTPRequestFake(src._socketFD, src._logger),
      _hTTPResponseFake(src._socketFD, src._logger),
	  _hTTPServletManager(src._socketFD, src._logger){
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

void ProtocolManagerHTTPFake::servlet() {
  _hTTPServletManager.doService(_hTTPRequestFake, _hTTPResponseFake);
}

void ProtocolManagerHTTPFake::createResponse() {
  _hTTPResponseFake.createResponse();
}

void ProtocolManagerHTTPFake::connectionHitTheTimeout() {
   _hTTPServletManager.doError(HTTPStatus::TIMEOUT, _hTTPResponseFake);
   _hTTPResponseFake.createResponse();
}