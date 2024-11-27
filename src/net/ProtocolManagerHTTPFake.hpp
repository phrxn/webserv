#ifndef NET_PROTOCOL_MANAGER_HTTP_FAKE_HPP
#define NET_PROTOCOL_MANAGER_HTTP_FAKE_HPP

#include "../error/Log.hpp"
#include "HTTPRequestFake.hpp"
#include "HTTPResponseFake.hpp"
#include "ProtocolManager.hpp"
#include "SocketFileDescriptor.hpp"

class ProtocolManagerHTTPFake : public ProtocolManager {
 public:
  ProtocolManagerHTTPFake(SocketFileDescriptor *socket, Log *_logger);
  ~ProtocolManagerHTTPFake();

  RequestCreationStatus createRequest();
  void servlet();
  void createResponse();
  void connectionHitTheTimeout();

 private:
  ProtocolManagerHTTPFake(const ProtocolManagerHTTPFake &src);
  ProtocolManagerHTTPFake &operator=(const ProtocolManagerHTTPFake &src);

  HTTPRequestFake _hTTPRequestFake;
  HTTPResponseFake _hTTPResponseFake;
  SocketFileDescriptor *_socketFD;
  Log *_logger;
};

#endif