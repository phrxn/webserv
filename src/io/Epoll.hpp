#ifndef IO_EPOLL_HPP
#define IO_EPOLL_HPP

#include <map>

#include "../error/Log.hpp"
#include "../system/Errno.hpp"
#include "../system/SystemCalls.hpp"
#include "FileDescriptor.hpp"
#include "Poll.hpp"

class Epoll : public Poll {
 public:
  Epoll(Log *logger);

  ~Epoll();

  bool createPoll();
  bool addFileDescriptor(FileDescriptor *fd, EVENTS_TO_LISTENER option);
  bool removeFileDescriptor(FileDescriptor *fd);
  bool changeOptionFileDescriptor(FileDescriptor *fd,
                                  EVENTS_TO_LISTENER option);
  std::vector<FileDescriptor *> wait();
  std::map<int, FileDescriptor *> &getFileDescriptorsInPoll();

  void prepareStructEpollEvent(int fd, EVENTS_TO_LISTENER option,
                               struct epoll_event *event);

  int getFileDescriptor() const;

  void setFileDescriptorEvents(FileDescriptor *fd, struct epoll_event &event);

  void setSystemCalls(SystemCalls *SystemCalls);

 private:
  Epoll(const Epoll &src);
  Epoll &operator=(const Epoll &src);

  Log *_logger;
  SystemCalls *_systemCalls;

  int _epollFileDescriptor;
  std::vector<struct epoll_event> _events;
  std::map<int, FileDescriptor *> _mapFileDescriptorsToManager;
};

#endif