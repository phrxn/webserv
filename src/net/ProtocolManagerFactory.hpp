#ifndef NET_PROTOCOL_MANAGER_FACTORY_HPP
#define NET_PROTOCOL_MANAGER_FACTORY_HPP

#include "../config/ProgramConfiguration.hpp"
#include "../config/Variables.hpp"
#include "../error/Log.hpp"
#include "ProtocolManager.hpp"
#include "SocketFileDescriptor.hpp"

class ProtocolManagerFactory {
 public:
  ProtocolManagerFactory(Log *logger, ProgramConfiguration &_configuration);
  virtual ~ProtocolManagerFactory();
  virtual ProtocolManager *createProtocolManager(SocketFileDescriptor *socketFd);

 private:
  ProtocolManagerFactory(const ProtocolManagerFactory &src);
  ProtocolManagerFactory &operator=(const ProtocolManagerFactory &src);

  Log *_logger;
  ProgramConfiguration &_configuration;
};

#endif