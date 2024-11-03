#ifndef NET_PROTOCOL_MANAGER_FACTORY_HPP
#define NET_PROTOCOL_MANAGER_FACTORY_HPP

#include "../error/Log.hpp"
#include "ProtocolManager.hpp"
#include "SocketFileDescriptor.hpp"

class ProtocolManagerFactory {
 public:
  enum TypesOfProtocol { ENTER, HTTP };

  ProtocolManagerFactory(Log *logger);
  virtual ~ProtocolManagerFactory();
  virtual ProtocolManager *createProtocolManager(
      TypesOfProtocol typeOfProtocol, SocketFileDescriptor *socketFd);

 private:
  ProtocolManagerFactory(const ProtocolManagerFactory &src);
  ProtocolManagerFactory &operator=(const ProtocolManagerFactory &src);

  Log *_logger;
};

#endif