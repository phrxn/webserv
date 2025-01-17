#include "GenericServer.hpp"

#include "../config/ProgramConfiguration.hpp"
#include "GenericServerRequestManager.hpp"
#include "ServerSocketFileDescriptor.hpp"
#include "SocketFileDescriptor.hpp"

GenericServer::GenericServer(Poll &poll, Log &log, ProgramConfiguration &configuration)
    : _poll(poll), _log(log), _configuration(configuration) {}

// deleted (this class MUST BE UNIQUE!)
GenericServer::GenericServer(const GenericServer &src)
    : _poll(src._poll), _log(src._log), _configuration(src._configuration) {
  *this = src;
}

GenericServer::~GenericServer() {
  for (std::map<FileDescriptor *, GenericServerRequestManager *>::iterator it =
           _mapClientRequestHandler.begin();
       it != _mapClientRequestHandler.end(); ++it) {
    delete it->first;
    delete it->second;
  }
}

// deleted (this class MUST BE UNIQUE!)
GenericServer &GenericServer::operator=(const GenericServer &src) {
  (void)src;
  return *this;
}

void GenericServer::processFilesDescriptorsReady(
    std::vector<FileDescriptor *> &vectorFD) {
  _log.log(Log::DEBUG, "GenericServer", "processFilesDescriptorsReady",
           "file descriptors ready", "");
  for (std::vector<FileDescriptor *>::iterator it = vectorFD.begin();
       it != vectorFD.end(); ++it) {
    (*it)->acceptVisit(this);
  }
}

void GenericServer::processClientRequest(
    SocketFileDescriptorImpl *clientSocket) {
  std::map<FileDescriptor *, GenericServerRequestManager *>::iterator it =
      _mapClientRequestHandler.find(clientSocket);

  if (it == _mapClientRequestHandler.end()) {
    _log.log(Log::ERROR, "GenericServer", "processClientRequest",
             "The client doesn't have a generic server request manager",
             clientSocket->getFileDescriptor());
    return;
  }

  _log.log(Log::DEBUG, "GenericServer", "processClientRequest",
           "client ready to I/0 fd:", clientSocket->getFileDescriptor());

  FileDescriptor *fileDescriptor = it->first;
  GenericServerRequestManager *gsrm = it->second;

  GenericServerRequestManager::Stage stage = gsrm->handler();
  if (stage != GenericServerRequestManager::RESET_TO_NEW_REQUESTS &&
      stage != GenericServerRequestManager::DESTROY) {
    return;
  }

  if (stage == GenericServerRequestManager::RESET_TO_NEW_REQUESTS) {
    _log.log(Log::INFO, "GenericServer", "processClientRequest",
             "resetting things to process a new request. fd:",
             clientSocket->getFileDescriptor());
    gsrm->resetForANewRequest();
    return;
  }

  _log.log(Log::INFO, "GenericServer", "processClientRequest",
           "remove client request from server fd:",
           clientSocket->getFileDescriptor());
  _poll.removeFileDescriptor(fileDescriptor);
  _mapClientRequestHandler.erase(it);
  delete fileDescriptor;
  delete gsrm;
}

void GenericServer::createANewClientRequestHandler(
    ServerSocketFileDescriptor *serverSocket) {
  _log.log(Log::DEBUG, "GenericServer", "createANewClientRequestHandler",
           "a new client was create to server socket on port:",
           serverSocket->getListenPort());

  SocketFileDescriptorImpl *client = serverSocket->createSocketClient();

  if (!client) return;

  GenericServerRequestManager *gsrm =
      new GenericServerRequestManager(&_poll, client, &_log, _configuration);

  addAnewGenericServerRequestManager(client, gsrm);

  _poll.addFileDescriptor(client, Poll::INPUT);
}

void GenericServer::addAnewGenericServerRequestManager(
    FileDescriptor *client, GenericServerRequestManager *gsrm) {
  std::pair<FileDescriptor *, GenericServerRequestManager *>
      newClientRequestManager;
  newClientRequestManager.first = client;
  newClientRequestManager.second = gsrm;
  _mapClientRequestHandler.insert(newClientRequestManager);
}

void GenericServer::closeRequestInactives() {
  for (std::map<FileDescriptor *, GenericServerRequestManager *>::iterator it =
           _mapClientRequestHandler.begin();
       it != _mapClientRequestHandler.end(); ++it) {
    GenericServerRequestManager *gsrmCheckTimeout = it->second;
    gsrmCheckTimeout->checkTimeOut();
  }
}

void GenericServer::doForServerSocketFileDescriptor(
    ServerSocketFileDescriptor *serverSocket) {
  createANewClientRequestHandler(serverSocket);
}

void GenericServer::doForSocketFileDescriptorImp(
    SocketFileDescriptorImpl *clientSocket) {
  processClientRequest(clientSocket);
}

std::map<FileDescriptor *, GenericServerRequestManager *> &
GenericServer::getMapClientRequestHandler() {
  return _mapClientRequestHandler;
}