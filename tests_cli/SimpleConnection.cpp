#include "SimpleConnection.hpp"

#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <limits>
#include <string>

#include "ThreadReceiveMessage.hpp"

void SimpleConnection::getInformationsToConnectWithServer() {
  std::cout << "Type the server IP or (type 1 to localhost): ";
  std::cin >> _serverHostname;
  if (_serverHostname == "1") _serverHostname = "127.0.0.1";
  std::cout << "Port number: ";
  std::cin >> _serverPort;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int SimpleConnection::startConnectionWithServer() {
  _socket = socketClient.createSocketClient(_serverHostname, _serverPort);
  if (_socket == -1) return -1;

  ThreadReceiveMessage threadReceive(&_recvThread, &_socket);
  threadReceive.startThread();

  return 0;
}

int SimpleConnection::sendMessageToServer(std::string &message) {
  ssize_t sended = 1;

  while (true) {
    sended = send(_socket, message.c_str(), message.length(), 0);
    if (sended == -1) break;
    if ((size_t)sended < message.length()) {
      message.erase(0, sended);
      continue;
    }
    break;
  }

  return sended;
}

// -1 error
// 0 not try reconnect
// 1 reconnected
int SimpleConnection::tryReconnect() {
  std::string option;

  std::cout << "Try reconnect? (yes/no): ";
  std::getline(std::cin, option);
  if (option != "yes") return 0;
  if (startConnectionWithServer() == -1) return -1;
  return 1;
}

void showConnectionMenu() {
  std::cout << "Connected with server..." << std::endl;
  std::cout << std::endl;
  std::cout << "\tTo send 'enter character' type: 1" << std::endl;
  std::cout << "\tTo exit type: q" << std::endl;
  std::cout << "\tWrite messages to server..." << std::endl;
}

void SimpleConnection::startSimpleConnection() {
  getInformationsToConnectWithServer();

  if (startConnectionWithServer() == -1) return;

  showConnectionMenu();

  std::string messageToServer;

  while (messageToServer != "q") {
    // read a line without \n
    std::getline(std::cin, messageToServer);

    if (messageToServer == "q") {
      int socketTmp = _socket;
      _socket = -1;
	  shutdown(socketTmp, SHUT_RDWR);
      close(socketTmp);
      return;
    }

    if (messageToServer == "1") {
      messageToServer = "\n";
    }

    if (messageToServer == "\n")
      std::cout << "\033[1;32mSending to server\033[0m: [(enter character)]\n"
                << std::endl;
    else
      std::cout << "\033[1;32mSending to server\033[0m: [" << messageToServer
                << "]" << std::endl;
    int writed = sendMessageToServer(messageToServer);
    if (writed == -1) {
      std::cout << "The connection with the server was closed." << std::endl;
      int tryRec = tryReconnect();
      if (tryRec < 1) return;
      showConnectionMenu();
    }
  }
}