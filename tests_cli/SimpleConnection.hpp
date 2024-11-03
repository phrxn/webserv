#ifndef SIMPLE_CONNECTION_HPP
#define SIMPLE_CONNECTION_HPP

#include <pthread.h>

#include <string>

#include "SocketClient.hpp"

class SimpleConnection {
 public:
  void startSimpleConnection();
  void getInformationsToConnectWithServer();
  int startConnectionWithServer();
  int sendMessageToServer(std::string &message);
  int tryReconnect();

 private:
  int _socket;
  pthread_t _recvThread;

  std::string _serverHostname;
  int _serverPort;

  SocketClient socketClient;

};

#endif