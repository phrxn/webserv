#include "ProtocolManagerEnter.hpp"

#include <iostream>
ProtocolManagerEnter::ProtocolManagerEnter(SocketFileDescriptor *socketFd,
                                           Log *logger)
    : _socketFd(*socketFd), _logger(logger) {
  _buffer += "Response: ";
}
ProtocolManagerEnter::~ProtocolManagerEnter() {}

// deleted (this class MUST BE UNIQUE!)
ProtocolManagerEnter::ProtocolManagerEnter(const ProtocolManagerEnter &src)
    : _socketFd(src._socketFd) {}

// deleted (this class MUST BE UNIQUE!)
ProtocolManagerEnter &ProtocolManagerEnter::operator=(
    const ProtocolManagerEnter &src) {
  (void)src;
  return *this;
}

ProtocolManager::RequestCreationStatus ProtocolManagerEnter::createRequest() {
  std::vector<char> &date = _socketFd.getInputStream();

  std::string strTmp(date.begin(), date.begin() + date.size());

  _logger->log(Log::DEBUG, "ProtocolManagerEnter", "createRequest",
               "input stream size:", date.size());

  date.clear();

  _buffer += strTmp;

  _logger->log(Log::DEBUG, "ProtocolManagerEnter", "createRequest",
               "the buffer:", _buffer);

  if (_buffer.find('\n') == std::string::npos) return REQUEST_CREATING;

  return REQUEST_CREATED;
}

void ProtocolManagerEnter::servlet() {
  _logger->log(Log::DEBUG, "ProtocolManagerEnter", "servlet",
               "not implemented...", "");
}

void ProtocolManagerEnter::createResponse() {
  _logger->log(Log::DEBUG, "ProtocolManagerEnter", "createResponse",
               "the buffer:", _buffer);
  _logger->log(Log::DEBUG, "ProtocolManagerEnter", "createResponse",
               "output stream size before the buffer is written:",
               _socketFd.getOutputStream().size());

  _socketFd.getOutputStream().assign(_buffer.begin(),
                                     _buffer.begin() + _buffer.size());
  _socketFd.setCloseSocketAfterProcessingResponse(false);
  _buffer.clear();

  _logger->log(Log::DEBUG, "ProtocolManagerEnter", "createResponse",
               "output stream size after the buffer is written:",
               _socketFd.getOutputStream().size());
}

void ProtocolManagerEnter::connectionHitTheTimeout() {
  _buffer = "Response: Timeout ... :(\n";

  _logger->log(Log::DEBUG, "ProtocolManagerEnter", "connectionHitTheTimeout",
               "the buffer:", _buffer);
  _logger->log(Log::DEBUG, "ProtocolManagerEnter", "connectionHitTheTimeout",
               "output stream size before the buffer is written:",
               _socketFd.getOutputStream().size());

  _socketFd.getOutputStream().assign(_buffer.begin(),
                                     _buffer.begin() + _buffer.size());
  _socketFd.setCloseSocketAfterProcessingResponse(false);
  _buffer.clear();

  _logger->log(Log::DEBUG, "ProtocolManagerEnter", "connectionHitTheTimeout",
               "output stream size after the buffer is written:",
               _socketFd.getOutputStream().size());
}