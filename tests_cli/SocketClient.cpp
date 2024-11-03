#include "SocketClient.hpp"

#include <arpa/inet.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#include "ThreadReceiveMessage.hpp"

SocketClient::SocketClient() {}

int SocketClient::createSocketClient(std::string server, int port) {
  // create TCP socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    std::cerr << "Error creating socket: " << strerror(errno) << std::endl;
    return -1;
  }

  // address configuration
  sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);

  int status = inet_pton(AF_INET, server.c_str(), &serv_addr.sin_addr);

  if (status <= 0) {
    if (status < 0)
      std::cerr << "inet_pton: error: " << strerror(errno) << std::endl;
    if (status == 0)
      std::cerr << "inet_pton: Invalid or unsupported address: " << std::endl;
    close(sockfd);
    return -1;
  }

  // connection with server
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    std::cerr << "Error connecting to server: " << strerror(errno) << std::endl;
    close(sockfd);
    return -1;
  }

  return sockfd;
}
