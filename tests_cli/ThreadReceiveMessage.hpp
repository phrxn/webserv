#ifndef THREAD_RECEIVE_MESSAGE_HPP
#define THREAD_RECEIVE_MESSAGE_HPP

#include <pthread.h>

void *receiveMessages(void *socket_des);

class ThreadReceiveMessage {
 public:
  static const int BUFFER_SIZE = 256;

  ThreadReceiveMessage(pthread_t *recvThread, int *socketFileDescriptor);
  bool startThread();

 private:

  pthread_t *_recvThread;
  int *_socketFileDescriptor;
};

#endif