#include "ServerSocketFileDescriptor.hpp"

#include <sstream>

#include "../error/StatusOr.hpp"
#include "../system/Errno.hpp"
#include "Address.hpp"

ServerSocketFileDescriptor::ServerSocketFileDescriptor(Log *log)
    : FileDescriptor(-1), _logger(log){};

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

  Address localAddress(port, Address::LOCAL);

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

  serverSocket =
      _systemCalls->bind(_fd, (struct sockaddr *)localAddress.getAddress(),
                         sizeof(*localAddress.getAddress()));

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
  Address socketClientAddress;

  error::StatusOr<int> clientSocket = _systemCalls->accept(
      _fd, 0, (socklen_t *)sizeof(*(socketClientAddress.getAddress())));

  if (!clientSocket.ok()) {
    _logger->log(Log::FATAL, "ServerSocketFileDescriptor", "createSocketClient",
                 clientSocket.status().message(), "");
    return NULL;
  }

  int socketClientFileDescriptor = clientSocket.value();

  _logger->log(Log::INFO, "ServerSocketFileDescriptor", "createSocketClient",
               "a new client connection has been created. fd:",
               socketClientFileDescriptor);

  SocketFileDescriptorImpl *newSocketClient =
      new SocketFileDescriptorImpl(socketClientFileDescriptor, _logger);

  newSocketClient->setServerPort(_listenPort);

  return newSocketClient;
}

void ServerSocketFileDescriptor::acceptVisit(FileDescriptorVisitor *fdv) {
  fdv->doForServerSocketFileDescriptor(this);
}