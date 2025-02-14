#ifndef NET_SERVER_SOCKET_FILE_DESCRIPTOR_HPP
#define NET_SERVER_SOCKET_FILE_DESCRIPTOR_HPP

#include <netinet/in.h>

#include <string>

#include "../error/Log.hpp"
#include "../error/StatusOr.hpp"
#include "../io/FileDescriptor.hpp"
#include "FileDescriptorVisitor.hpp"
#include "SocketFileDescriptorImpl.hpp"

// class for marking only
class ServerSocketFileDescriptor : public FileDescriptor {
 public:
  ServerSocketFileDescriptor(Log *log);
  ~ServerSocketFileDescriptor();

  bool createSocketServer(int port);

  SocketFileDescriptorImpl *createSocketClient();
  int getListenPort() const;

  std::string getSocketClientIPv4(uint32_t ipv4);

  int getLocalClientPort(int  socketClientFD);

  void acceptVisit(FileDescriptorVisitor *fdv);

 private:
  ServerSocketFileDescriptor(const ServerSocketFileDescriptor &src);
  ServerSocketFileDescriptor &operator=(const ServerSocketFileDescriptor &src);

  int _listenPort;
  Log *_logger;
};

#endif