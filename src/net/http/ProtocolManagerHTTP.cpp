#include "ProtocolManagerHTTP.hpp"

ProtocolManagerHTTP::ProtocolManagerHTTP(SocketFileDescriptor *socket,
                                         Log *logger)
    : _logger(logger),
      _hTTPRequest(socket, logger),
      _hTTPResponse(socket),
      _hTTPServletManager(socket, logger),
      _socketFD(socket) {}

ProtocolManagerHTTP::~ProtocolManagerHTTP() {}

ProtocolManager::RequestCreationStatus ProtocolManagerHTTP::createRequest() {
  if (_hTTPRequest.createRequest() == Request::REQUEST_CREATING)
    return REQUEST_CREATING;
  return REQUEST_CREATED;
}

// deleted (this class MUST BE UNIQUE!)
ProtocolManagerHTTP::ProtocolManagerHTTP(const ProtocolManagerHTTP &src)
    : _hTTPRequest(src._socketFD, src._logger),
      _hTTPResponse(src._socketFD),
      _hTTPServletManager(src._socketFD, src._logger) {
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
  _hTTPServletManager.doError(HTTPStatus::TIMEOUT, _hTTPResponse);
  _hTTPResponse.createResponse();
}
