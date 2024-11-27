#ifndef NET_PROTOCOL_MANAGER_HTTP_HPP
#define NET_PROTOCOL_MANAGER_HTTP_HPP

#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include "HTTPServletManager.hpp"
#include "ProtocolManager.hpp"
#include "SocketFileDescriptor.hpp"

class ProtocolManagerHTTP : public ProtocolManager {
 public:
  ProtocolManagerHTTP(SocketFileDescriptor *socket);
  ~ProtocolManagerHTTP();

  RequestCreationStatus createRequest();
  void servlet();
  void createResponse();
  void connectionHitTheTimeout();

 private:
  ProtocolManagerHTTP(const ProtocolManagerHTTP &src);
  ProtocolManagerHTTP &operator=(const ProtocolManagerHTTP &src);

  HTTPRequest _hTTPRequest;
  HTTPResponse _hTTPResponse;
  HTTPServletManager _hTTPServletManager;
  SocketFileDescriptor *_socketFD;

};

#endif