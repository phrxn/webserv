#include "ServerSocketFileDescriptor.hpp"

#include <sstream>

#include "../error/StatusOr.hpp"
#include "../system/Errno.hpp"

ServerSocketFileDescriptor::ServerSocketFileDescriptor(Log *log)
    : FileDescriptor(-1), _logger(log) {};

ServerSocketFileDescriptor::~ServerSocketFileDescriptor() {}

// deleted (this class MUST BE UNIQUE!)
ServerSocketFileDescriptor::ServerSocketFileDescriptor(
    const ServerSocketFileDescriptor &src)
    : FileDescriptor(src), _logger(src._logger) {
  (void)src;
}

// deleted (this class MUST BE UNIQUE!)
ServerSocketFileDescriptor &ServerSocketFileDescriptor::operator=(
    const ServerSocketFileDescriptor &src) {
  (void)src;
  return *this;
}

// return: true if server socket was created
bool ServerSocketFileDescriptor::createSocketServer(int port) {
  _listenPort = port;

  struct sockaddr_in addressIPv4;
  addressIPv4.sin_family = AF_INET;
  addressIPv4.sin_port = htons(port);
  addressIPv4.sin_addr.s_addr = INADDR_ANY;

  error::StatusOr<int> serverSocket =
      _systemCalls->socket(PF_INET, SOCK_STREAM, 0);

  if (!serverSocket.ok()) {
    _logger->log(Log::FATAL, "ServerSocketFileDescriptor", "createSocketServer",
                 serverSocket.status().message(), port);
    return false;
  }

  // here the socket fd is valid!
  _fd = serverSocket.value();

  int yes = 1;
  serverSocket =
      _systemCalls->setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
  if (!serverSocket.ok()) {
    _logger->log(Log::FATAL, "ServerSocketFileDescriptor", "createSocketServer",
                 serverSocket.status().message(), port);
    return false;
  }

  serverSocket = _systemCalls->bind(_fd, (struct sockaddr *)&addressIPv4,
                                    sizeof(addressIPv4));

  if (!serverSocket.ok()) {
    _logger->log(Log::FATAL, "ServerSocketFileDescriptor", "createSocketServer",
                 serverSocket.status().message(), port);
    return false;
  }

  serverSocket = _systemCalls->listen(_fd, 10);

  if (!serverSocket.ok()) {
    _logger->log(Log::FATAL, "ServerSocketFileDescriptor", "createSocketServer",
                 serverSocket.status().message(), port);
    return false;
  }

  return true;
}

int ServerSocketFileDescriptor::getListenPort() const { return _listenPort; }

// return null if any errors occurs
SocketFileDescriptorImpl *ServerSocketFileDescriptor::createSocketClient() {
  struct sockaddr_in addressIPv4;
  socklen_t addrLen = sizeof(addressIPv4);

  error::StatusOr<int> clientSocket =
      _systemCalls->accept(_fd, (struct sockaddr *)&addressIPv4, &addrLen);

  if (!clientSocket.ok()) {
    _logger->log(Log::FATAL, "ServerSocketFileDescriptor", "createSocketClient",
                 clientSocket.status().message(), "");
    return NULL;
  }

  int socketClientFD = clientSocket.value();

  int socketRemoteClientPort = ntohs(addressIPv4.sin_port);

  std::string clientIPv4 = getSocketClientIPv4(addressIPv4.sin_addr.s_addr);

  getLocalClientPort(socketClientFD);

  _logger->log(Log::INFO, "ServerSocketFileDescriptor", "createSocketClient",
               "a new client connection has been created. fd:", socketClientFD);

  SocketFileDescriptorImpl *newSocketClient =
      new SocketFileDescriptorImpl(socketClientFD, _logger);

  newSocketClient->setServerPort(_listenPort);
  newSocketClient->setRemoteClientPort(socketRemoteClientPort);
  newSocketClient->setClientIPv4(clientIPv4);

  return newSocketClient;
}

std::string ServerSocketFileDescriptor::getSocketClientIPv4(uint32_t ipv4) {
  uint32_t ipv4Host = ntohl(ipv4);

  unsigned char bytes[4];
  bytes[0] = (ipv4Host >> 24) & 0xFF;
  bytes[1] = (ipv4Host >> 16) & 0xFF;
  bytes[2] = (ipv4Host >> 8) & 0xFF;
  bytes[3] = ipv4Host & 0xFF;

  std::ostringstream oss;
  oss << static_cast<int>(bytes[0]) << "." << static_cast<int>(bytes[1]) << "."
      << static_cast<int>(bytes[2]) << "." << static_cast<int>(bytes[3]);

  return oss.str();
}

int ServerSocketFileDescriptor::getLocalClientPort(int socketClientFD) {
  struct sockaddr_in addressIPv4;
  socklen_t addrLen = sizeof(addressIPv4);

  error::StatusOr<int> clientSocket = _systemCalls->getsockname(
      socketClientFD, (struct sockaddr *)&addressIPv4, &addrLen);

  if (!clientSocket.ok()) {
    _logger->log(Log::ERROR, "ServerSocketFileDescriptor", "getLocalClientPort",
                 clientSocket.status().message(), "");
    return -1;
  }

  int port = ntohs(addressIPv4.sin_port);

  return port;
}

void ServerSocketFileDescriptor::acceptVisit(FileDescriptorVisitor *fdv) {
  fdv->doForServerSocketFileDescriptor(this);
}
