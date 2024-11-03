#ifndef SOCKET_CLIENT_HPP
#define SOCKET_CLIENT_HPP

#include <pthread.h>

#include <string>

class SocketClient {
 public:
  SocketClient();
  int createSocketClient(std::string address, int port);
};

#endif