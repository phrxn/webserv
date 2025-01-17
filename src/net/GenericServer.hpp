#ifndef NET_GENERIC_SERVER_HPP
#define NET_GENERIC_SERVER_HPP

#include <map>
#include <vector>

#include "../error/Log.hpp"
#include "../io/FileDescriptor.hpp"
#include "../io/Poll.hpp"
#include "FileDescriptorVisitor.hpp"
#include "GenericServerRequestManager.hpp"
#include "SocketFileDescriptorImpl.hpp"

class GenericServer : public FileDescriptorVisitor {
 public:
  GenericServer(Poll &poll, Log &log, ProgramConfiguration &configuration);
  ~GenericServer();

  void processFilesDescriptorsReady(std::vector<FileDescriptor *> &vectorFD);

  void processClientRequest(SocketFileDescriptorImpl *clientSocket);

  void createANewClientRequestHandler(ServerSocketFileDescriptor *server);

  void closeRequestInactives();

  std::map<FileDescriptor *, GenericServerRequestManager *>
      &getMapClientRequestHandler();

  void addAnewGenericServerRequestManager(FileDescriptor *client,
                                          GenericServerRequestManager *gsrm);

  void doForServerSocketFileDescriptor(ServerSocketFileDescriptor *);

  void doForSocketFileDescriptorImp(SocketFileDescriptorImpl *);

 private:
  GenericServer(const GenericServer &src);
  GenericServer &operator=(const GenericServer &src);

  Poll &_poll;
  Log &_log;
  ProgramConfiguration &_configuration;
  std::map<FileDescriptor *, GenericServerRequestManager *>
      _mapClientRequestHandler;
};

#endif