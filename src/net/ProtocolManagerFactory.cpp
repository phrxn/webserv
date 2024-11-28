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

ProtocolManager *ProtocolManagerFactory::createProtocolManager(
    SocketFileDescriptor *socketFd) {

  if (_configuration.getTypeOfProtocol() == ENTER) {
    _logger->log(Log::WARNING, "ProtocolManagerFactory",
                 "createProtocolManager", "the protocol is ENTER", "");
    return new ProtocolManagerEnter(socketFd, _logger);
  }

  if (_configuration.getEnvironment() == TEST) {
    _logger->log(Log::WARNING, "ProtocolManagerFactory",
                 "createProtocolManager", "webserv is in the test environment",
                 "");
    return new ProtocolManagerHTTPFake(socketFd, _logger);
  }

  _logger->log(Log::INFO, "ProtocolManagerFactory", "createProtocolManager",
               "the configured protocol is HTTP", "");
  return new ProtocolManagerHTTP(socketFd);
}