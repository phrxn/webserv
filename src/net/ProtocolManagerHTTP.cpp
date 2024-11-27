#include "ProtocolManagerHTTP.hpp"

ProtocolManagerHTTP::ProtocolManagerHTTP(SocketFileDescriptor *socket)
    : _hTTPRequest(socket),
      _hTTPResponse(socket),
      _hTTPServletManager(socket),
      _socketFD(socket) {}

ProtocolManagerHTTP::~ProtocolManagerHTTP() {}

ProtocolManager::RequestCreationStatus ProtocolManagerHTTP::createRequest() {
  if (_hTTPRequest.createRequest() == Request::REQUEST_CREATING)
    return REQUEST_CREATING;
  return REQUEST_CREATED;
}

// deleted (this class MUST BE UNIQUE!)
ProtocolManagerHTTP::ProtocolManagerHTTP(const ProtocolManagerHTTP &src)
    : _hTTPRequest(src._socketFD),
      _hTTPResponse(src._socketFD),
      _hTTPServletManager(src._socketFD) {
  (void)src;
}

// deleted (this class MUST BE UNIQUE!)
ProtocolManagerHTTP &ProtocolManagerHTTP::operator=(
    const ProtocolManagerHTTP &src) {
  (void)src;
  return *this;
}

void ProtocolManagerHTTP::servlet() {
  _hTTPServletManager.doService(_hTTPRequest, _hTTPResponse);
}

void ProtocolManagerHTTP::createResponse() { _hTTPResponse.createResponse(); }

void ProtocolManagerHTTP::connectionHitTheTimeout() {
  _hTTPServletManager.doError(408, _hTTPResponse);
}
