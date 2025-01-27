#include "Start.hpp"

#include <iostream>

#include "Webserv.hpp"
#include "error/LogDefault.hpp"
#include "io/Epoll.hpp"
#include "net/ServerSocketFileDescriptor.hpp"
#include "net/http/MimeType.hpp"
#include "start/CreateMimeTypeMap.hpp"

void disableSignals() {
  signal(SIGINT, SIG_IGN);
  signal(SIGTERM, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
  signal(SIGPIPE, SIG_IGN);
}

void setupSignal(void (*handleSignal)(int)) {
  signal(SIGINT, handleSignal);
  signal(SIGTERM, handleSignal);
  signal(SIGQUIT, handleSignal);
  signal(SIGPIPE, SIG_IGN);
}

void Start::handleSignal(int sig) {
  (void)sig;
  Webserv::continueRunningTheServer = false;

  switch (sig) {
    case SIGINT:
      LogDefault::loggerGlobal->log(Log::WARNING, "Start", "handleSignal", "Interrupt",
                        "closing the server");
      break;
    case SIGTERM:
      LogDefault::loggerGlobal->log(Log::WARNING, "Start", "handleSignal", "Terminate",
                        "closing the server");
      break;
    case SIGQUIT:
     LogDefault::loggerGlobal->log(Log::WARNING, "Start", "handleSignal", "Quit",
                        "closing the server");
      break;
    default:
      break;
  }
}

Start::Start(const char **environmentVariables)
    : _logger(NULL),
      _poll(NULL),
      _programConfiguration(ProgramConfiguration::getInstance()),
      _environmentVariables(environmentVariables),
      _loaderOfProgramFiles(_logger) {}

Start::~Start() {
  if (_logger) delete _logger;
  if (_poll) delete _poll;

  std::list<ServerSocketFileDescriptor *>::const_iterator it =
      _listServerSocketFileDescriptor.begin();
  std::list<ServerSocketFileDescriptor *>::const_iterator end =
      _listServerSocketFileDescriptor.end();

  for (; it != end; ++it) {
    delete *it;
  }
}

void Start::startTheProgram(int argc, char **argv) {
  disableSignals();

  createProgramConfiguration();

  startLog();

  if (!_loaderOfProgramFiles.loaderAllProgramThings(argc, argv)) {
    return;
  }

  if (!startTheServerSockets()) {
    return;
  }

  if (!startPoll()) {
    return;
  }

  setupSignal(handleSignal);

  startWebserver(*_poll, *_logger, _programConfiguration);

  exitingFromProgram();
}

void Start::exitingFromProgram() {
  _logger->log(Log::INFO, "Start", "exiting From Program", "Exiting...", "");
}

// deleted (this class MUST BE UNIQUE!)
Start::Start(const Start &src)
    : _programConfiguration(ProgramConfiguration::getInstance()),
      _loaderOfProgramFiles(src._logger) {
  (void)src;
  *this = src;
}

// deleted (this class MUST BE UNIQUE!)
Start &Start::operator=(const Start &src) {
  (void)src;
  return *this;
}

void Start::createProgramConfiguration() {
  _programConfiguration.setEnvironment(TEST);
  _programConfiguration.setTypeOfProtocol(HTTP);
  _programConfiguration.setTimeOutForNewRequestOrToSendAFullRequest(5);
  _programConfiguration.setLogLevel(Log::DEBUG);
  _programConfiguration.setEnvironmentVariables(_environmentVariables);

  //5MB
  _programConfiguration.setMaxRequestSizeInBytes(5242880);
}

void Start::startLog() {
  _logger = new LogDefault(_programConfiguration.getLogLevel());
  _logger->startLogger();
  _logger->log(Log::INFO, "Start", "startLog", "create log default", "");

  if (!LogDefault::loggerGlobal) {
    LogDefault::loggerGlobal = _logger;
  }
  _loaderOfProgramFiles.setLogger(_logger);
}

bool Start::startTheServerSockets() {
  const std::list<int> &allServerPortsNeed =
      _loaderOfProgramFiles.getListOfAllVirtualHostPorts();

  std::list<int>::const_iterator it = allServerPortsNeed.begin();
  std::list<int>::const_iterator end = allServerPortsNeed.end();

  if (allServerPortsNeed.size() == 0){
    _logger->log(Log::FATAL, "Start", "startTheServerSocket",
                 "the configuration file must have at least one port", "");
	return false;
  }

  for (; it != end; ++it) {
    ServerSocketFileDescriptor *ssd = new ServerSocketFileDescriptor(_logger);
	_listServerSocketFileDescriptor.push_back(ssd);
    if (!ssd->createSocketServer(*it)) {
      return false;
    }
    _logger->log(Log::INFO, "Start", "startTheServerSocket",
                 "waiting for clients on port:", *it);
  }
  return true;
}

bool Start::startPoll() {
  _logger->log(Log::INFO, "Start", "startPoll",
               "start the poll to wait clients", "");

  _poll = new Epoll(_logger);

  if (!_poll->createPoll()) return false;

  std::list<ServerSocketFileDescriptor *>::const_iterator it =
      _listServerSocketFileDescriptor.begin();
  std::list<ServerSocketFileDescriptor *>::const_iterator end =
      _listServerSocketFileDescriptor.end();

  for (; it != end; ++it) {
    if (!_poll->addFileDescriptor(*it, Poll::INPUT)) {
      return false;
    }
  }

  return true;
}

void Start::startWebserver(Poll &poll, Log &logger,
                           ProgramConfiguration &configuration) {
  Webserv webserv(poll, logger, configuration);
  webserv.start();
}
