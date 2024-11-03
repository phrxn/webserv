#include "ThreadReceiveMessage.hpp"

#include <sys/socket.h>

#include <cstring>
#include <iostream>
#include <vector>

ThreadReceiveMessage::ThreadReceiveMessage(pthread_t *recvThread,
                                           int *socketFileDescriptor)
    : _recvThread(recvThread), _socketFileDescriptor(socketFileDescriptor) {}

bool ThreadReceiveMessage::startThread() {

  int status = pthread_create(_recvThread, nullptr, receiveMessages,
                              _socketFileDescriptor);

  if (status != 0) {
    std::cerr << "Error creating thread (ThreadReceiveMessage). Error code: "
              << status << " ."
              << "Error Message: " << strerror(status) << std::endl;
    return false;
  }

  status = pthread_detach(*_recvThread);

  if (status != 0) {
    std::cerr << "Error detach thread (ThreadReceiveMessage). Error code: "
              << status << " ."
              << "Error Message: " << strerror(status) << std::endl;
    return false;
  }

  return true;
}

void *receiveMessages(void *socket_des) {

  char bufferTmp[ThreadReceiveMessage::BUFFER_SIZE];
  std::vector<char> buffer;

  int _socketFileDescriptor = *(int *)socket_des;

  std::string errorMessage;

  while (true) {
    memset(bufferTmp, 0, sizeof(bufferTmp));

    ssize_t bytesReceived = recv(_socketFileDescriptor, bufferTmp,
                                 ThreadReceiveMessage::BUFFER_SIZE, 0);

	if (*(int*)socket_des == -1)
	  break;

    if (bytesReceived < 0) {
      errorMessage = strerror(errno);
    }

    if (bytesReceived < 0) {
      std::cerr << "\033[1;31mError receiving message:\033[0m " << errorMessage << std::endl;
	  *(int*)socket_des = -1;
      return NULL;
    }
    if (bytesReceived == 0) {
      std::cerr << "\033[1;31mThe server close the connection.\033[0m" << std::endl;
	  *(int*)socket_des = -1;
      return NULL;
    }

    std::cout << "\033[1;36mamount of bytes received:\033[0m " << bytesReceived << std::endl;
    buffer.insert(buffer.end(), bufferTmp, bufferTmp + bytesReceived);

    if (bytesReceived == ThreadReceiveMessage::BUFFER_SIZE) continue;

    std::cout << "\033[1;36mMessage from server:\033[0m ["
              << std::string(buffer.begin(), buffer.end()) << "]" << std::endl;
    std::cout << "-----------------------------" << std::endl;

    buffer.clear();
  }
  return NULL;
}