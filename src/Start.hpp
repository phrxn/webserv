#ifndef START_HPP
#define START_HPP

#include <csignal>

#include "config/ProgramConfiguration.hpp"
#include "error/LogDefault.hpp"
#include "io/Poll.hpp"
#include "net/ServerSocketFileDescriptor.hpp"
#include "start/LoaderOfProgramFiles.hpp"
#include "system/SystemCalls.hpp"

class Start {
 public:
  static void handleSignal(int sig);
  static LogDefault *loggerGlobal;

  Start(const char **environmentVariables);
  ~Start();

  void startTheProgram(int argc, char **argv);

 private:
  Start(const Start &src);
  Start &operator=(const Start &src);

  void createProgramConfiguration();
  void startLog();
  ServerSocketFileDescriptor *startTheServerSocket();
  bool startPoll(ServerSocketFileDescriptor *ssfd);
  void startWebserver(Poll &poll, Log &logger,
                      ProgramConfiguration &configuration);
  void exitingFromProgram();

 private:
  LogDefault *_logger;
  Poll *_poll;
  SystemCalls systemCalls;
  ServerSocketFileDescriptor *_ssfd;
  ProgramConfiguration &_programConfiguration;
  const char **_environmentVariables;
  LoaderOfProgramFiles _loaderOfProgramFiles;
};

#endif