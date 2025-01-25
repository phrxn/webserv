#ifndef START_HPP
#define START_HPP

#include <csignal>
#include <list>

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
  bool startTheServerSockets();
  bool startPoll();
  void startWebserver(Poll &poll, Log &logger,
                      ProgramConfiguration &configuration);
  void exitingFromProgram();

 private:
  LogDefault *_logger;
  Poll *_poll;
  SystemCalls systemCalls;
  std::list<ServerSocketFileDescriptor*> _listServerSocketFileDescriptor;
  ProgramConfiguration &_programConfiguration;
  const char **_environmentVariables;
  LoaderOfProgramFiles _loaderOfProgramFiles;
};

#endif