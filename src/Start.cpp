#include "Start.hpp"

#include <iostream>

#include "Webserv.hpp"
#include "error/LogDefault.hpp"
#include "io/Epoll.hpp"
#include "net/ServerSocketFileDescriptor.hpp"
#include "net/http/MimeType.hpp"
#include "start/CreateMimeTypeMap.hpp"

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

Start::Start(const char **environmentVariables)
    : _logger(NULL),
      _poll(NULL),
	  _ssfd(NULL),
      _programConfiguration(ProgramConfiguration::getInstance()),
      _environmentVariables(environmentVariables) {}

Start::~Start() {
  if (_logger) delete _logger;
  if (_poll) delete _poll;
  if (_ssfd) delete _ssfd;
}

void Start::startTheProgram() {
  createProgramConfiguration();

  startLog();

  if (!loadMimetypeListFromFile(_logger)) {
    return;
  }

  _ssfd = startTheServerSocket();
  if (!_ssfd) return;

  if (!startPoll(_ssfd)) return;

  setupSignal(handleSignal);

  startWebserver(*_poll, *_logger, _programConfiguration);

  exitingFromProgram();
}

void Start::exitingFromProgram() {
  _logger->log(Log::INFO, "Start", "exiting From Program", "Exiting...", "");
}

// deleted (this class MUST BE UNIQUE!)
Start::Start(const Start &src)
    : _programConfiguration(ProgramConfiguration::getInstance()) {
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
  _programConfiguration.setLogLevel(Log::INFO);
  _programConfiguration.setEnvironmentVariables(_environmentVariables);
}

void Start::startLog() {
  _logger = new LogDefault(_programConfiguration.getLogLevel());
  _logger->startLogger();
  _logger->log(Log::INFO, "Start", "startLog", "create log default", "");

  if (!loggerGlobal) loggerGlobal = _logger;
}

bool Start::loadMimetypeListFromFile(Log *logger) {
  CreateMimeTypeMap createMimetypeMap;

  error::StatusOr<std::map<std::string, std::string> > mimeMap =
      createMimetypeMap.loadMimetypeMap("conf/mime.types");

  if (!mimeMap.ok()) {
    logger->log(Log::FATAL, "Start", "loadMimetypeListFromFile",
                "create the mimeType map", mimeMap.status().message());
    return false;
  }

  MimeType::setMimetypeMap(mimeMap.value());

  return true;
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

void Start::startWebserver(Poll &poll, Log &logger,
                           ProgramConfiguration &configuration) {
  Webserv webserv(poll, logger, configuration);
  webserv.start();
}
