#include "ProtocolManagerFactory.hpp"

#include "../config/Variables.hpp"
#include "ProtocolManagerEnter.hpp"
#include "ProtocolManagerHTTP.hpp"
#include "ProtocolManagerHTTPFake.hpp"

ProtocolManagerFactory::ProtocolManagerFactory(Log *logger,
                                               Configuration &configuration)
    : _logger(logger), _configuration(configuration) {}

ProtocolManagerFactory::~ProtocolManagerFactory() {}

// deleted (this class MUST BE UNIQUE!)
ProtocolManagerFactory::ProtocolManagerFactory(
    const ProtocolManagerFactory &src)
    : _configuration(src._configuration) {
  (void)src;
}

// deleted (this class MUST BE UNIQUE!)
ProtocolManagerFactory &ProtocolManagerFactory::operator=(
    const ProtocolManagerFactory &src) {
  (void)src;
  return *this;
}

ProtocolManager *ProtocolManagerFactory::createProtocolManager(SocketFileDescriptor *socketFd) {

  if (_configuration.getTypeOfProtocol() == ENTER)
    return new ProtocolManagerEnter(socketFd, _logger);

  if (_configuration.getEnvironment() == TEST)
    return new ProtocolManagerHTTPFake(socketFd, _logger);

  return new ProtocolManagerHTTP(socketFd);
}