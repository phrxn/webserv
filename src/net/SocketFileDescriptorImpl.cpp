#include "SocketFileDescriptorImpl.hpp"

#include "../error/StatusOr.hpp"

const int SocketFileDescriptorImpl::SOCKET_CLIENT_READ_BUFFER_SIZE = 4096;

SocketFileDescriptorImpl::SocketFileDescriptorImpl(int fd, Log *logger)
    : SocketFileDescriptor(fd),
      _bufferResize(SOCKET_CLIENT_READ_BUFFER_SIZE),
      _logger(logger) {}

SocketFileDescriptorImpl::SocketFileDescriptorImpl(int fd, size_t bufferResize,
                                                   Log *logger)
    : SocketFileDescriptor(fd), _bufferResize(bufferResize), _logger(logger) {}

SocketFileDescriptorImpl::~SocketFileDescriptorImpl() {}

// deleted (this class MUST BE UNIQUE!)
SocketFileDescriptorImpl::SocketFileDescriptorImpl(
    const SocketFileDescriptorImpl &src)
    : SocketFileDescriptor(src), _logger(src._logger) {
  (void)src;
}

// deleted (this class MUST BE UNIQUE!)
SocketFileDescriptor &SocketFileDescriptorImpl::operator=(
    const SocketFileDescriptorImpl &src) {
  (void)src;
  return *this;
}

// return: true if the reading was done, otherwise false is returned
bool SocketFileDescriptorImpl::doRead() {
  std::size_t oldSize = _vectorInputStream.size();
  std::size_t resize = oldSize + _bufferResize;
  _vectorInputStream.resize(resize);
  char *position = _vectorInputStream.data() + oldSize;

  error::StatusOr<ssize_t> sysReaded =
      _systemCalls->read(_fd, position, _bufferResize);

  if (!sysReaded.ok()) {
    _logger->log(Log::ERROR, "SocketFileDescriptorImpl", "doRead",
                 "could not read data from client socket", _fd);
    return false;
  }

  size_t readed = sysReaded.value();

  _logger->log(Log::DEBUG, "SocketFileDescriptorImpl", "doRead",
               "read from client fd:", _fd);
  _logger->log(Log::DEBUG, "SocketFileDescriptorImpl", "doRead",
               "number of bytes:", readed);

  if (readed < _bufferResize) _vectorInputStream.resize(readed);

  if (readed == 0) {
    _logger->log(Log::ERROR, "SocketFileDescriptorImpl", "doRead",
                 "the client closed the connection", _fd);
    return false;
  }

  return true;
}

// return:
//   The number of bytes from the buffer that remain to be written to the
//   socket.
//   if  0 is returned, means that everything has been written.
//   if -1 is returned an error occurred while writing.
ssize_t SocketFileDescriptorImpl::doWrite() {
  error::StatusOr<ssize_t> writed = _systemCalls->write(
      _fd, _vectorOutputStream.data(), _vectorOutputStream.size());
  _logger->log(Log::DEBUG, "SocketFileDescriptorImpl", "doWrite",
               "vector outputStrem size:", _vectorOutputStream.size());

  if (!writed.ok()) {
    _logger->log(Log::ERROR, "SocketFileDescriptorImpl", "doWrite",
                 "error writing response to client fd:", _fd);
    _logger->log(
        Log::ERROR, "SocketFileDescriptorImpl", "doWrite",
        "error writing response to client error:", writed.status().message());
    return -1;
  }

  std::string strWrite(_vectorOutputStream.begin(),
                       _vectorOutputStream.begin() + writed.value());
  _logger->log(Log::DEBUG, "SocketFileDescriptorImpl", "doWrite",
               "chars writed to client:\n", strWrite);

  _vectorOutputStream.erase(_vectorOutputStream.begin(),
                            _vectorOutputStream.begin() + writed.value());

  return _vectorOutputStream.size();
}

void SocketFileDescriptorImpl::acceptVisit(FileDescriptorVisitor *fdv) {
  fdv->doForSocketFileDescriptorImp(this);
}