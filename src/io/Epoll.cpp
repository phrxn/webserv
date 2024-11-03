#include "Epoll.hpp"

#include <cstring>
#include <iostream>

#include "../error/StatusOr.hpp"

Epoll::Epoll(Log *logger)
    : _logger(logger), _systemCalls(new SystemCalls), _epollFileDescriptor(-1) {
  _events.reserve(10);
}

Epoll::~Epoll() {
  if (_systemCalls) delete _systemCalls;
}

// private
Epoll::Epoll(const Epoll &src)
    : _logger(src._logger), _systemCalls(src._systemCalls) {
  (void)src;
}

// private
Epoll &Epoll::operator=(const Epoll &src) {
  (void)src;
  return *this;
}

bool Epoll::createPoll() {
  if (_epollFileDescriptor != -1) {
    _logger->log(Log::ERROR, "Epoll", "createPoll",
                 "The poll has already been created", "");
    return false;
  }

  error::StatusOr<int> createFd = _systemCalls->epoll_create(1);
  if (!createFd.ok()) {
    _logger->log(Log::FATAL, "Epoll", "createPoll", createFd.status().message(),
                 "");
    return false;
  }

  _epollFileDescriptor = createFd.value();
  return true;
}

bool Epoll::addFileDescriptor(FileDescriptor *fd,
                              Poll::EVENTS_TO_LISTENER option) {
  struct epoll_event event;
  prepareStructEpollEvent(fd->getFileDescriptor(), option, &event);

  error::StatusOr<int> addFdToEpoll = _systemCalls->epoll_ctl(
      _epollFileDescriptor, EPOLL_CTL_ADD, fd->getFileDescriptor(), &event);
  if (!addFdToEpoll.ok()) {
    _logger->log(Log::ERROR, "Epoll", "addFileDescriptor(",
                 addFdToEpoll.status().message(), "");
    return false;
  }

  std::pair<int, FileDescriptor *> pair(fd->getFileDescriptor(), fd);

  _mapFileDescriptorsToManager.insert(pair);

  return true;
}

bool Epoll::removeFileDescriptor(FileDescriptor *fd) {
  std::map<int, FileDescriptor *>::iterator it =
      _mapFileDescriptorsToManager.find(fd->getFileDescriptor());

  if (it == _mapFileDescriptorsToManager.end()) {
    _logger->log(Log::ERROR, "Epoll", "removeFileDescriptor",
                 "The file descriptor doesn't exist in epoll",
                 fd->getFileDescriptor());
    return false;
  }

  error::StatusOr<int> removeFdFromEpoll = _systemCalls->epoll_ctl(
      _epollFileDescriptor, EPOLL_CTL_DEL, fd->getFileDescriptor(), NULL);
  if (!removeFdFromEpoll.ok()) {
    _logger->log(Log::ERROR, "Epoll", "removeFileDescriptor",
                 removeFdFromEpoll.status().message(), fd->getFileDescriptor());
    return false;
  }

  _mapFileDescriptorsToManager.erase(it);

  return true;
}

bool Epoll::changeOptionFileDescriptor(FileDescriptor *fd,
                                       Poll::EVENTS_TO_LISTENER option) {
  std::map<int, FileDescriptor *>::iterator it =
      _mapFileDescriptorsToManager.find(fd->getFileDescriptor());

  if (it == _mapFileDescriptorsToManager.end()) {
    _logger->log(Log::ERROR, "Epoll", "changeOptionFileDescriptor",
                 "The file descriptor doesn't exist in epoll",
                 fd->getFileDescriptor());
    return false;
  }

  int fdToChange = fd->getFileDescriptor();

  struct epoll_event event;
  prepareStructEpollEvent(fdToChange, option, &event);

  error::StatusOr<int> changeFdModOnThePoll = _systemCalls->epoll_ctl(
      _epollFileDescriptor, EPOLL_CTL_MOD, fdToChange, &event);
  if (!changeFdModOnThePoll.ok()) {
    _logger->log(Log::ERROR, "Epoll", "changeOptionFileDescriptor",
                 changeFdModOnThePoll.status().message(),
                 fd->getFileDescriptor());
    return false;
  }

  return true;
}

std::vector<FileDescriptor *> Epoll::wait() {
  ssize_t listSize = _mapFileDescriptorsToManager.size();

  std::vector<FileDescriptor *> listfileDescriptorReady;

  if (listSize == 0) return listfileDescriptorReady;

  _events.reserve(listSize);

  error::StatusOr<int> waitEvents = _systemCalls->epoll_wait(
      _epollFileDescriptor, _events.data(), listSize, 1);
  if (!waitEvents.ok()) {
    _logger->log(Log::ERROR, "Epoll", "wait", waitEvents.status().message(),
                 "");
    return listfileDescriptorReady;
  }

  int fileDescriptorsReady = waitEvents.value();

  for (int i = 0; i < fileDescriptorsReady; ++i) {
    int fd = _events[i].data.fd;

    FileDescriptor *fdReady = _mapFileDescriptorsToManager[fd];

    setFileDescriptorEvents(fdReady, _events[i]);

    listfileDescriptorReady.push_back(fdReady);
  }

  return listfileDescriptorReady;
}

std::map<int, FileDescriptor *> &Epoll::getFileDescriptorsInPoll() {
  return _mapFileDescriptorsToManager;
}

void Epoll::prepareStructEpollEvent(int fd, Poll::EVENTS_TO_LISTENER option,
                                    struct epoll_event *event) {
  memset(event, 0, sizeof(*event));
  event->data.fd = fd;
  event->events = 0;

  if (option == Poll::NOTHING) event->events = 0;
  if (option == Poll::INPUT || option == Poll::INPUT_AND_OUTPUT)
    event->events |= EPOLLIN;
  if (option == Poll::OUTPUT || option == Poll::INPUT_AND_OUTPUT)
    event->events |= EPOLLOUT;
}

int Epoll::getFileDescriptor() const { return _epollFileDescriptor; }

void Epoll::setFileDescriptorEvents(FileDescriptor *fdReady,
                                    struct epoll_event &event) {
  fdReady->setReadyToRead((event.events & EPOLLIN) ? true : false);
  fdReady->setReadyToWrite((event.events & EPOLLOUT) ? true : false);
}

void Epoll::setSystemCalls(SystemCalls *systemCalls) {
  if (_systemCalls) delete _systemCalls;
  _systemCalls = systemCalls;
}