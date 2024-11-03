#ifndef START_HPP
#define START_HPP

#include <csignal>

#include "error/LogDefault.hpp"
#include "io/Poll.hpp"
#include "net/ServerSocketFileDescriptor.hpp"
#include "system/SystemCalls.hpp"

class Start {
 public:
  static void handleSignal(int sig);
  static LogDefault *loggerGlobal;

  Start();
  ~Start();

  void startTheProgram();

 private:
  Start(const Start &src);
  Start &operator=(const Start &src);

  void startLog();
  ServerSocketFileDescriptor *startTheServerSocket();
  bool startPoll(ServerSocketFileDescriptor *ssfd);
  void startWebserver(Poll &poll, Log &logger);
  void exitingFromProgram();

 private:
  LogDefault *_logger;
  Poll *_poll;
  SystemCalls systemCalls;
  ServerSocketFileDescriptor *_ssfd;
};

#endif