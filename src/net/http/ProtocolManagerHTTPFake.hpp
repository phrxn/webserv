#ifndef NET_HTTP_PROTOCOL_MANAGER_HTTP_FAKE_HPP
#define NET_HTTP_PROTOCOL_MANAGER_HTTP_FAKE_HPP

#include "../../error/Log.hpp"
#include "../ProtocolManager.hpp"
#include "../SocketFileDescriptor.hpp"
#include "HTTPServletManager.hpp"
#include "HTTPRequestFake.hpp"
#include "HTTPResponseFake.hpp"

class ProtocolManagerHTTPFake : public ProtocolManager {
 public:
  ProtocolManagerHTTPFake(Log *_logger, SocketFileDescriptor *socket);
  ~ProtocolManagerHTTPFake();

  RequestCreationStatus createRequest();
  void servlet();
  void createResponse();
  void connectionHitTheTimeout();

 private:
  ProtocolManagerHTTPFake(const ProtocolManagerHTTPFake &src);
  ProtocolManagerHTTPFake &operator=(const ProtocolManagerHTTPFake &src);

  Log *_logger;
  HTTPRequestFake _hTTPRequestFake;
  HTTPResponseFake _hTTPResponseFake;
  HTTPServletManager _hTTPServletManager;
  SocketFileDescriptor *_socketFD;

};

#endif