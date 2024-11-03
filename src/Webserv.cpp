#include "Webserv.hpp"

#include <vector>

bool Webserv::continueRunningTheServer = true;

Webserv::Webserv(Poll &poll, Log &log)
    : _poll(poll), _log(log), _genericServer(poll, log) {}

Webserv::~Webserv() {}

// private
Webserv::Webserv(const Webserv &src)
    : _poll(src._poll), _log(src._log), _genericServer(src._poll, src._log) {
  *this = src;
}

// private
Webserv &Webserv::operator=(const Webserv &src) {
  (void)src;
  return *this;
}

void Webserv::start() {
  while (continueRunningTheServer) {
    std::vector<FileDescriptor *> vectorFileDescriptorsReady = _poll.wait();
    if (vectorFileDescriptorsReady.size() > 0) {
      _genericServer.processFilesDescriptorsReady(vectorFileDescriptorsReady);
    }
    _genericServer.closeRequestInactives();
  }
}