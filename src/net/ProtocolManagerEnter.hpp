#ifndef NET_PROTOCOL_MANAGER_ENTER_HPP
#define NET_PROTOCOL_MANAGER_ENTER_HPP

#include <string>

#include "../error/Log.hpp"
#include "ProtocolManager.hpp"
#include "SocketFileDescriptor.hpp"

class ProtocolManagerEnter : public ProtocolManager {
 public:
  ProtocolManagerEnter(SocketFileDescriptor *socketFd, Log *logger);
  ~ProtocolManagerEnter();
  ProtocolManagerEnter(const ProtocolManagerEnter &src);
  ProtocolManagerEnter &operator=(const ProtocolManagerEnter &src);

  RequestCreationStatus createRequest();
  void servlet();
  void createResponse();
  void connectionHitTheTimeout();

 private:
  SocketFileDescriptor &_socketFd;
  Log *_logger;
  std::string _buffer;
};

#endif