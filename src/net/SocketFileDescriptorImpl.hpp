#ifndef NET_SOCKET_FILE_DESCRIPTOR_IMPL
#define NET_SOCKET_FILE_DESCRIPTOR_IMPL

#include "../error/Log.hpp"
#include "../system/Errno.hpp"
#include "SocketFileDescriptor.hpp"

class SocketFileDescriptorImpl : public SocketFileDescriptor {
 public:
  static const int SOCKET_CLIENT_READ_BUFFER_SIZE;

  SocketFileDescriptorImpl(int fd, Log *logger);
  SocketFileDescriptorImpl(int fd, size_t bufferResize, Log *log);
  SocketFileDescriptorImpl(int fd, const Address &_address, size_t bufferResize,
                           Log *log);
  ~SocketFileDescriptorImpl();

  virtual bool doRead();
  virtual ssize_t doWrite();

  void acceptVisit(FileDescriptorVisitor *fdv);

 private:
  SocketFileDescriptorImpl(const SocketFileDescriptorImpl &src);
  SocketFileDescriptor &operator=(const SocketFileDescriptorImpl &src);

  size_t _bufferResize;
  Log *_logger;
};

#endif