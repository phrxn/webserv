#ifndef NET_SOCKET_FILE_DESCRIPTOR_HPP
#define NET_SOCKET_FILE_DESCRIPTOR_HPP

#include <vector>

#include "../io/FileDescriptor.hpp"
#include "../system/SystemCalls.hpp"
#include "Address.hpp"
#include "FileDescriptorVisitor.hpp"

class SocketFileDescriptor : public FileDescriptor {
 public:
  SocketFileDescriptor(int fd);
  SocketFileDescriptor(int fd, const Address &_address);
  virtual ~SocketFileDescriptor();

  std::vector<char> &getInputStream();
  std::vector<char> &getOutputStream();

  void setCloseSocketAfterProcessingResponse(bool isToClose);
  virtual bool isForCloseSocketAfterProcessingResponse() const;
  void setServerPort(int serverPort);
  int  getServerPort() const;

 protected:
  SocketFileDescriptor(const SocketFileDescriptor &src);

  std::vector<char> _vectorInputStream;
  std::vector<char> _vectorOutputStream;
  Address _address;

 private:
  SocketFileDescriptor &operator=(const SocketFileDescriptor &src);

  // Tells whether the socket should be closed after the request response
  // has been sent.
  bool _closeSocketAfterProcessingResponse;
  int _serverPort;
};

#endif