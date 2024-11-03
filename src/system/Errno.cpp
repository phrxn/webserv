#include "Errno.hpp"

#include <cerrno>
#include <cstring>

Errno::Errno() {}

Errno::Errno(const Errno &src) { (void)src; }

Errno::~Errno() {}

Errno &Errno::operator=(const Errno &src) {
  (void)src;
  return *this;
}

std::string Errno::getErrorMessage() const {
  int errorCode = errno;
  return std::string(strerror(errorCode));
}