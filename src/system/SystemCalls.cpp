#include "SystemCalls.hpp"

#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

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

error::StatusOr<int> SystemCalls::stat(const char *_file,
                                       struct stat *_buf) const {
  int status = ::stat(_file, _buf);
  if (status == -1) {
    return error::Status(error::Status::SystemCall, createErrorMessage("stat"));
  }
  return status;
}

error::StatusOr<int> SystemCalls::access(const char *name, int type) const {
  int status = ::access(name, type);
  if (status == -1) {
    return error::Status(error::Status::SystemCall,
                         createErrorMessage("access"));
  }
  return status;
}

error::StatusOr<int> SystemCalls::open(const char *name, int flags,
                                       mode_t mode) const {
  int status = ::open(name, flags, mode);

  if (status == -1) {
    return error::Status(error::Status::SystemCall, createErrorMessage("open"));
  }

  return status;
}

error::StatusOr<int> SystemCalls::dup2(int oldfd, int newfd) const {
  int status = ::dup2(oldfd, newfd);

  if (status == -1) {
    return error::Status(error::Status::SystemCall, createErrorMessage("dup2"));
  }

  return status;
}

error::StatusOr<pid_t> SystemCalls::waitpid(pid_t pid, int *stat_loc, int options) const{
	pid_t status = ::waitpid(pid, stat_loc, options);

	if (status == -1) {
		return error::Status(error::Status::SystemCall, createErrorMessage("waitpid"));
	}
	return status;
}

error::StatusOr<int> SystemCalls::kill(pid_t pid, int sig) const{
	int status = ::kill(pid, sig);

	if (status == -1) {
		return error::Status(error::Status::SystemCall, createErrorMessage("kill"));
	}
	return status;

}

error::StatusOr<pid_t> SystemCalls::fork(void) const{
	pid_t status = ::fork();

	if (status == -1) {
		return error::Status(error::Status::SystemCall, createErrorMessage("fork"));
	}
	return status;
}

std::string SystemCalls::createErrorMessage(
    const std::string &systemCallName) const {
  std::stringstream errorMessage;
  errorMessage << systemCallName << ": " << _theErrno.getErrorMessage();
  return errorMessage.str();
}