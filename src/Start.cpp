#include "Start.hpp"

#include <iostream>

#include "Webserv.hpp"
#include "error/LogDefault.hpp"
#include "io/Epoll.hpp"
#include "net/ServerSocketFileDescriptor.hpp"

LogDefault *Start::loggerGlobal = NULL;

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
      loggerGlobal->log(Log::WARNING, "Start", "handleSignal", "Interrupt",
                        "closing the server");
      break;
    case SIGTERM:
      loggerGlobal->log(Log::WARNING, "Start", "handleSignal", "Terminate",
                        "closing the server");
      break;
    case SIGQUIT:
      loggerGlobal->log(Log::WARNING, "Start", "handleSignal", "Quit",
                        "closing the server");
      break;
    default:
      break;
  }
}

Start::Start() : _logger(NULL), _poll(NULL) {}

Start::~Start() {
  if (_logger) delete _logger;
  if (_poll) delete _poll;
  if (_ssfd) delete _ssfd;
}

void Start::startTheProgram() {
  startLog();

  _ssfd = startTheServerSocket();
  if (!_ssfd) return;

  if (!startPoll(_ssfd)) return;

  setupSignal(handleSignal);

  createConfiguration();

  startWebserver(*_poll, *_logger, _configuration);

  exitingFromProgram();
}

void Start::exitingFromProgram() {
  _logger->log(Log::INFO, "Start", "exiting From Program", "Exiting...", "");
}

// deleted (this class MUST BE UNIQUE!)
Start::Start(const Start &src) {
  (void)src;
  *this = src;
}

// deleted (this class MUST BE UNIQUE!)
Start &Start::operator=(const Start &src) {
  (void)src;
  return *this;
}

void Start::createConfiguration(){
	_configuration.setEnvironment(TEST);
	_configuration.setTypeOfProtocol(HTTP);
}

void Start::startLog() {
  _logger = new LogDefault;
  _logger->startLogger();
  _logger->log(Log::INFO, "Start", "startLog", "create log default", "");

  if (!loggerGlobal) loggerGlobal = _logger;
}

ServerSocketFileDescriptor *Start::startTheServerSocket() {
  bool serverSocketWasCreated = false;
  int port = 8080;

  _logger->log(Log::INFO, "Start", "startTheServerSocket",
               "create the server sockets", "");

  ServerSocketFileDescriptor *ssfd = new ServerSocketFileDescriptor(_logger);

  serverSocketWasCreated = ssfd->createSocketServer(port);
  if (!serverSocketWasCreated) {
    delete ssfd;
    ssfd = NULL;
  }

  _logger->log(Log::INFO, "Start", "startTheServerSocket",
               "waiting for clients on port:", port);

  return ssfd;
}

bool Start::startPoll(ServerSocketFileDescriptor *ssfd) {
  _logger->log(Log::INFO, "Start", "startPoll",
               "start the poll to wait clients", "");

  _poll = new Epoll(_logger);

  if (!_poll->createPoll()) return false;

  if (!_poll->addFileDescriptor(ssfd, Poll::INPUT)) return false;

  return true;
}

void Start::startWebserver(Poll &poll, Log &logger, Configuration &configuration) {
  Webserv webserv(poll, logger, configuration);
  webserv.start();
}
