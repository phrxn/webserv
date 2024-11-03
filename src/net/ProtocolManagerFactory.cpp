#include "ProtocolManagerFactory.hpp"

#include "ProtocolManagerEnter.hpp"

ProtocolManagerFactory::ProtocolManagerFactory(Log *logger) : _logger(logger) {}
ProtocolManagerFactory::~ProtocolManagerFactory() {}

// private
ProtocolManagerFactory::ProtocolManagerFactory(
    const ProtocolManagerFactory &src) {
  (void)src;
}
// private
ProtocolManagerFactory &ProtocolManagerFactory::operator=(
    const ProtocolManagerFactory &src) {
  (void)src;
  return *this;
}

ProtocolManager *ProtocolManagerFactory::createProtocolManager(
    ProtocolManagerFactory::TypesOfProtocol typeOfProtocol,
    SocketFileDescriptor *socketFd) {
  (void)typeOfProtocol;

  // ** ADD THE HTTP PROTOCOL **
  // if (typeOfProtocol == ProtocolManagerFactory::HTTP)
  // return new ProtocolManagerEnter(socketFd);
  return new ProtocolManagerEnter(socketFd, _logger);
}