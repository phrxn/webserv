#ifndef START_HPP
#define START_HPP

#include <csignal>

#include "config/Configuration.hpp"
#include "error/LogDefault.hpp"
#include "io/Poll.hpp"
#include "net/ServerSocketFileDescriptor.hpp"
#include "system/SystemCalls.hpp"

class Start {
 public:
  static void handleSignal(int sig);
  static LogDefault *loggerGlobal;

  Start(const char **environmentVariables);
  ~Start();

  void startTheProgram();

 private:
  Start(const Start &src);
  Start &operator=(const Start &src);

  void createConfiguration();
  void startLog();
  ServerSocketFileDescriptor *startTheServerSocket();
  bool startPoll(ServerSocketFileDescriptor *ssfd);
  void startWebserver(Poll &poll, Log &logger, Configuration &configuration);
  void exitingFromProgram();

 private:
  LogDefault *_logger;
  Poll *_poll;
  SystemCalls systemCalls;
  Configuration &_configuration;
  ServerSocketFileDescriptor *_ssfd;
  const char **_environmentVariables;

};

#endif