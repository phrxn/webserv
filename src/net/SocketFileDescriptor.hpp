#ifndef NET_SOCKET_FILE_DESCRIPTOR_HPP
#define NET_SOCKET_FILE_DESCRIPTOR_HPP

#include <string>
#include <vector>

#include "../io/FileDescriptor.hpp"
#include "../system/SystemCalls.hpp"
#include "FileDescriptorVisitor.hpp"

class SocketFileDescriptor : public FileDescriptor {
 public:
  SocketFileDescriptor(int fd);
  virtual ~SocketFileDescriptor();

  std::vector<char> &getInputStream();
  std::vector<char> &getOutputStream();

  void setCloseSocketAfterProcessingResponse(bool isToClose);
  virtual bool isForCloseSocketAfterProcessingResponse() const;
  void setServerPort(int serverPort);
  int  getServerPort() const;
  void setRemoteClientPort(int port);
  int getRemoteClientPort() const;
  void setClientIPv4(const std::string &ipv4);
  std::string getClientIPv4() const;

 protected:
  SocketFileDescriptor(const SocketFileDescriptor &src);

  std::vector<char> _vectorInputStream;
  std::vector<char> _vectorOutputStream;

 private:
  SocketFileDescriptor &operator=(const SocketFileDescriptor &src);

  // Tells whether the socket should be closed after the request response
  // has been sent.
  bool _closeSocketAfterProcessingResponse;
  int _serverPort;
  int _remoteClientPort;
  std::string _clientIPv4;
};

#endif