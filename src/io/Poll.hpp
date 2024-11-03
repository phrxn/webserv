#ifndef IO_POLL_HPP
#define IO_POLL_HPP

#include <sys/epoll.h>

#include <map>
#include <vector>

#include "FileDescriptor.hpp"

class Poll {
 public:
  enum EVENTS_TO_LISTENER {
    NOTHING,
    INPUT,
    OUTPUT,
    INPUT_AND_OUTPUT,
  };

  virtual ~Poll() = 0;

  virtual bool createPoll() = 0;
  virtual bool addFileDescriptor(FileDescriptor *fd,
                                 EVENTS_TO_LISTENER option) = 0;
  virtual bool removeFileDescriptor(FileDescriptor *fd) = 0;
  virtual bool changeOptionFileDescriptor(FileDescriptor *fd,
                                          EVENTS_TO_LISTENER option) = 0;
  virtual std::vector<FileDescriptor *> wait() = 0;
  virtual std::map<int, FileDescriptor *> &getFileDescriptorsInPoll() = 0;
};

#endif