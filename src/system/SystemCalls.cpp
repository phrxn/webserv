#include "SystemCalls.hpp"

#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <sstream>

SystemCalls::SystemCalls() {}

SystemCalls::~SystemCalls() {}

SystemCalls::SystemCalls(const SystemCalls &src) { (void)src; }

SystemCalls &SystemCalls::operator=(const SystemCalls &src) {
  (void)src;
  return *this;
}

error::StatusOr<int> SystemCalls::epoll_create(int size) const {
  int status = ::epoll_create(size);
  if (status == -1)
    return error::Status(error::Status::SystemCall,
                         createErrorMessage("epoll_create"));
  return status;
}

error::StatusOr<int> SystemCalls::epoll_ctl(int epfd, int op, int fd,
                                            struct epoll_event *event) const {
  int status = ::epoll_ctl(epfd, op, fd, event);
  if (status == -1)
    return error::Status(error::Status::SystemCall,
                         createErrorMessage("epoll_ctl"));
  return status;
}

error::StatusOr<int> SystemCalls::epoll_wait(int epfd,
                                             struct epoll_event *events,
                                             int maxevents, int timeout) const {
  int status = ::epoll_wait(epfd, events, maxevents, timeout);
  if (status == -1)
    return error::Status(error::Status::SystemCall,
                         createErrorMessage("epoll_wait"));
  return status;
}

error::StatusOr<int> SystemCalls::close(int fd) const {
  int status = ::close(fd);
  if (status == -1)
    return error::Status(error::Status::SystemCall,
                         createErrorMessage("close"));
  return status;
}

error::StatusOr<int> SystemCalls::socket(int socket_family, int socket_type,
                                         int protocol) const {
  int status = ::socket(socket_family, socket_type, protocol);
  if (status == -1)
    return error::Status(error::Status::SystemCall,
                         createErrorMessage("socket"));
  return status;
}

error::StatusOr<int> SystemCalls::setsockopt(int sockfd, int level, int optname,
                                             const void *optval,
                                             socklen_t optlen) const {
  int status = ::setsockopt(sockfd, level, optname, optval, optlen);
  if (status == -1)
    return error::Status(error::Status::SystemCall,
                         createErrorMessage("setsockopt"));
  return status;
}

error::StatusOr<int> SystemCalls::bind(int sockfd, const struct sockaddr *addr,
                                       socklen_t addrlen) const {
  int status = ::bind(sockfd, addr, addrlen);
  if (status == -1)
    return error::Status(error::Status::SystemCall, createErrorMessage("bind"));
  return status;
}

error::StatusOr<int> SystemCalls::listen(int socket, int backlog) const {
  int status = ::listen(socket, backlog);
  if (status == -1)
    return error::Status(error::Status::SystemCall,
                         createErrorMessage("listen"));
  return status;
}

error::StatusOr<ssize_t> SystemCalls::read(int fd, void *buf,
                                           size_t count) const {
  ssize_t readed = ::read(fd, buf, count);
  if (readed == -1)
    return error::Status(error::Status::SystemCall, createErrorMessage("read"));
  return readed;
}

error::StatusOr<ssize_t> SystemCalls::write(int fd, const void *buf,
                                            size_t count) const {
  ssize_t writed = ::write(fd, buf, count);
  if (writed == -1)
    return error::Status(error::Status::SystemCall,
                         createErrorMessage("write"));
  return writed;
}

error::StatusOr<int> SystemCalls::accept(int sockfd, struct sockaddr *addr,
                                         socklen_t *addrlen) const {
  int socketClientFd = ::accept(sockfd, addr, addrlen);
  if (socketClientFd == -1)
    return error::Status(error::Status::SystemCall,
                         createErrorMessage("accept"));
  return socketClientFd;
}

error::StatusOr<int> SystemCalls::getsockname(int sockfd, struct sockaddr *addr,
                                              socklen_t *addrlen) const {
  int status = ::getsockname(sockfd, addr, addrlen);
  if (status == -1) {
    return error::Status(error::Status::SystemCall,
                         createErrorMessage("getsockname"));
  }
  return status;
}

std::string SystemCalls::createErrorMessage(
    const std::string &systemCallName) const {
  std::stringstream errorMessage;
  errorMessage << systemCallName << ": " << _theErrno.getErrorMessage();
  return errorMessage.str();
}