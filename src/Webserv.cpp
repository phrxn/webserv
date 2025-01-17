#include "Webserv.hpp"

#include <vector>

#include "config/ProgramConfiguration.hpp"

bool Webserv::continueRunningTheServer = true;

Webserv::Webserv(Poll &poll, Log &log, ProgramConfiguration &configuration)
    : _poll(poll),
      _log(log),
      _configuration(configuration),
      _genericServer(poll, log, configuration) {}

Webserv::~Webserv() {}

// deleted (this class MUST BE UNIQUE!)
Webserv::Webserv(const Webserv &src)
    : _poll(src._poll),
      _log(src._log),
      _configuration(src._configuration),
      _genericServer(src._poll, src._log, src._configuration) {
  *this = src;
}

// deleted (this class MUST BE UNIQUE!)
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