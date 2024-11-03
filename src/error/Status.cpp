#include "Status.hpp"

namespace error {

Status::Status() : _code(OK){};
Status::Status(Code code) : _code(code), _message("") {}
Status::Status(Code code, const std::string &message)
    : _code(code), _message(message) {}
Status::Status(const Status &src) { *this = src; }

Status::~Status() {}

Status &Status::operator=(const Status &src) {
  if (this == &src) return *this;
  this->_code = src._code;
  this->_message = src._message;
  return *this;
}

bool Status::ok() const { return _code == OK; }

Status::Code Status::code() const { return _code; }

std::string Status::message() const { return _message; }
}  // namespace error