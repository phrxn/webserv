#ifndef SYSTEM_SYSTEM_CALLS
#define SYSTEM_SYSTEM_CALLS

#include <sys/socket.h>
#include <signal.h>
#include <sys/types.h>

#include "../error/StatusOr.hpp"
#include "Errno.hpp"

class SystemCalls {
 public:
  SystemCalls();
  SystemCalls(const SystemCalls &src);
  virtual ~SystemCalls();

  SystemCalls &operator=(const SystemCalls &src);

  virtual error::StatusOr<int> epoll_create(int size) const;
  virtual error::StatusOr<int> epoll_ctl(int epfd, int op, int fd,
                                         struct epoll_event *event) const;

  virtual error::StatusOr<int> epoll_wait(int epfd, struct epoll_event *events,
                                          int maxevents, int timeout) const;

  virtual error::StatusOr<int> close(int fd) const;

  virtual error::StatusOr<int> socket(int socket_family, int socket_type,
                                      int protocol) const;

  virtual error::StatusOr<int> setsockopt(int sockfd, int level, int optname,
                                          const void *optval,
                                          socklen_t optlen) const;

  virtual error::StatusOr<int> bind(int sockfd, const struct sockaddr *addr,
                                    socklen_t addrlen) const;

  virtual error::StatusOr<int> listen(int socket, int backlog) const;

  virtual error::StatusOr<ssize_t> read(int fd, void *buf, size_t count) const;

  virtual error::StatusOr<ssize_t> write(int fd, const void *buf,
                                         size_t count) const;

  virtual error::StatusOr<int> accept(int sockfd, struct sockaddr *addr,
                                      socklen_t *addrlen) const;

  virtual error::StatusOr<int> getsockname(int sockfd, struct sockaddr *addr,
                                           socklen_t *addrlen) const;

  virtual error::StatusOr<int> stat(const char *_file, struct stat *_buf) const;

  virtual error::StatusOr<int> access (const char *name, int type) const;

  virtual error::StatusOr<int> open(const char *name, int flags, mode_t mode) const;

  virtual error::StatusOr<int> dup2(int oldfd, int newfd) const;

  virtual error::StatusOr<pid_t> waitpid(pid_t pid, int *stat_loc, int options) const;

  virtual error::StatusOr<int> kill(pid_t pid, int sig) const;

  virtual error::StatusOr<pid_t> fork(void) const;

  virtual error::StatusOr<int> execve(const char *pathname, char *const argv[],
                  char *const envp[]) const;

 private:
  std::string createErrorMessage(const std::string &systemCallName) const;

  Errno _theErrno;
};

#endif
