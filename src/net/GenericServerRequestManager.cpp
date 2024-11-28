#include "GenericServerRequestManager.hpp"

#include "../config/Variables.hpp"

GenericServerRequestManager::GenericServerRequestManager(
    Poll *poll, SocketFileDescriptorImpl *socketFileDescriptor, Log *logger,
    Configuration &configuration)
    : _poll(poll),
      _socketFileDescriptor(socketFileDescriptor),
      _logger(logger),
      _managerStage(REQUEST_CREATING),
      _configuration(configuration) {
  setProtocolManager();

  _timeOfLastInputFromCLient = std::time(0);
}

GenericServerRequestManager::~GenericServerRequestManager() {
  if (_protocolManager) delete _protocolManager;
}

// deleted (this class MUST BE UNIQUE!)
GenericServerRequestManager::GenericServerRequestManager(
    const GenericServerRequestManager &src)
    : _poll(src._poll),
      _socketFileDescriptor(src._socketFileDescriptor),
      _logger(src._logger),
      _configuration(src._configuration) {
  (void)src;
  *this = src;
}

// deleted (this class MUST BE UNIQUE!)
GenericServerRequestManager &GenericServerRequestManager::operator=(
    const GenericServerRequestManager &src) {
  (void)src;
  return *this;
}

// return: true if no error occurred, otherwise false is returned
bool GenericServerRequestManager::readInputFromSocket() {
  _logger->log(Log::DEBUG, "GenericServerRequestManager", "handler",
               "wait protocol manager create request. fd:",
               _socketFileDescriptor->getFileDescriptor());

  bool makeSockedRead = _socketFileDescriptor->doRead();
  if (!makeSockedRead) return false;

  _timeOfLastInputFromCLient = std::time(0);
  return true;
}

GenericServerRequestManager::Stage
GenericServerRequestManager::createRequest() {
  ProtocolManager::RequestCreationStatus requestCreationStatus =
      _protocolManager->createRequest();
  if (requestCreationStatus == ProtocolManager::REQUEST_CREATING)
    return REQUEST_CREATING;

  _managerStage = PROCESS_SERVLET;

  _logger->log(Log::DEBUG, "GenericServerRequestManager", "handler",
               "protocol manager created request. fd:",
               _socketFileDescriptor->getFileDescriptor());
  return PROCESS_SERVLET;
}

void GenericServerRequestManager::doServlet() {
  _logger->log(Log::DEBUG, "GenericServerRequestManager", "handler",
               "wait protocol manager process servlet. fd:",
               _socketFileDescriptor->getFileDescriptor());

  _protocolManager->servlet();
  _poll->changeOptionFileDescriptor(_socketFileDescriptor, Poll::OUTPUT);
  _managerStage = RESPONSE;

  _logger->log(Log::DEBUG, "GenericServerRequestManager", "handler",
               "protocol manager processed servlet. fd:",
               _socketFileDescriptor->getFileDescriptor());
}

void GenericServerRequestManager::doTimeout() {
  _protocolManager->connectionHitTheTimeout();
  _poll->changeOptionFileDescriptor(_socketFileDescriptor, Poll::OUTPUT);
  _managerStage = WRITING_RESPONSE;

  _socketFileDescriptor->setCloseSocketAfterProcessingResponse(true);
}

void GenericServerRequestManager::doResponse() {
  _logger->log(Log::DEBUG, "GenericServerRequestManager", "handler",
               "wait protocol manager process response fd:",
               _socketFileDescriptor->getFileDescriptor());

  _protocolManager->createResponse();
  _managerStage = WRITING_RESPONSE;

  _logger->log(Log::DEBUG, "GenericServerRequestManager", "handler",
               "protocol manager processed response fd:",
               _socketFileDescriptor->getFileDescriptor());
}

GenericServerRequestManager::Stage
GenericServerRequestManager::doWritingResponse() {
  _logger->log(Log::DEBUG, "GenericServerRequestManager", "handler",
               "writing client response to fd:",
               _socketFileDescriptor->getFileDescriptor());

  ssize_t bytesToBeWritten = _socketFileDescriptor->doWrite();
  if (bytesToBeWritten == -1) return DESTROY;

  if (bytesToBeWritten > 0) return WRITING_RESPONSE;

  _logger->log(Log::INFO, "GenericServerRequestManager", "handler",
               "the response was all sent to the client. fd:",
               _socketFileDescriptor->getFileDescriptor());

  if (_socketFileDescriptor->isForCloseSocketAfterProcessingResponse())
    return DESTROY;
  return RESET_TO_NEW_REQUESTS;
}

GenericServerRequestManager::Stage GenericServerRequestManager::handler() {
  if (_managerStage == REQUEST_CREATING) {
    if (!readInputFromSocket()) return DESTROY;
    if (createRequest() == REQUEST_CREATING) return REQUEST_CREATING;
  }

  if (_managerStage == PROCESS_SERVLET) {
    doServlet();

    // let's return, at this moment the socket is only ready for reading,
    // in the next return of the poll the socket filedescriptor will be ready
    // for writing :)
    return RESPONSE;
  }

  if (_managerStage == TIME_OUT) {
    doTimeout();
  }

  if (_managerStage == RESPONSE) {
    doResponse();
  }

  if (_managerStage == WRITING_RESPONSE) {
    return doWritingResponse();
  }

  _logger->log(Log::FATAL, "GenericServerRequestManager", "handler",
               "Invalid protocol stage!", "");

  return DESTROY;
}

void GenericServerRequestManager::resetForANewRequest() {
  if (_protocolManager) delete _protocolManager;

  setProtocolManager();

  _poll->changeOptionFileDescriptor(_socketFileDescriptor, Poll::INPUT);
  _managerStage = REQUEST_CREATING;
}

// checks if 5 seconds have passed since the last input from the client
void GenericServerRequestManager::checkTimeOut() {
  // doesn't make sense to check the input timeout after protocol stage request
  if (_managerStage != REQUEST_CREATING) return;

  std::time_t timeNow = std::time(0);

  double diff = std::difftime(timeNow, _timeOfLastInputFromCLient);

  // checks if the last input time has passed the limit
  if (diff < _configuration.getTimeOutForNewRequestOrToSendAFullRequest())
    return;

  _logger->log(
      Log::WARNING, "GenericServerRequestManager", "checkTimeOut",
      "client timed out fd:", _socketFileDescriptor->getFileDescriptor());

  _managerStage = TIME_OUT;
  _poll->changeOptionFileDescriptor(_socketFileDescriptor, Poll::OUTPUT);
}

void GenericServerRequestManager::setProtocolManager(
    ProtocolManager *protocolManager) {
  _protocolManager = protocolManager;
}

void GenericServerRequestManager::setProtocolManager() {
  ProtocolManagerFactory pmf(_logger, _configuration);

  _protocolManager = pmf.createProtocolManager(_socketFileDescriptor);
}