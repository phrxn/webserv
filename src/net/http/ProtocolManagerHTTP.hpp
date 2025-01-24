#ifndef NET_HTTP_PROTOCOL_MANAGER_HTTP_HPP
#define NET_HTTP_PROTOCOL_MANAGER_HTTP_HPP

#include "../../error/Log.hpp"
#include "../ProtocolManager.hpp"
#include "../SocketFileDescriptor.hpp"
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include "HTTPServletManager.hpp"

class ProtocolManagerHTTP : public ProtocolManager {
 public:
  ProtocolManagerHTTP(SocketFileDescriptor *socket, Log *logger);
  ~ProtocolManagerHTTP();

  RequestCreationStatus createRequest();
  void servlet();
  void createResponse();
  void connectionHitTheTimeout();

 private:
  ProtocolManagerHTTP(const ProtocolManagerHTTP &src);
  ProtocolManagerHTTP &operator=(const ProtocolManagerHTTP &src);

  Log *_logger;
  HTTPRequest _hTTPRequest;
  HTTPResponse _hTTPResponse;
  HTTPServletManager _hTTPServletManager;
  SocketFileDescriptor *_socketFD;
};

#endif