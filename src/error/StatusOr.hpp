#ifndef ERROR_STATUS_OR_HPP
#define ERROR_STATUS_OR_HPP

#include "Status.hpp"

namespace error {

template <typename T>
class StatusOr {
 public:
  StatusOr(T value) : _value(value), _status(Status::OK) {}
  StatusOr(Status status) : _status(status) {}

  StatusOr(const StatusOr &src) : _value(src._value), _status(src._status){

  }

  StatusOr &operator=(const StatusOr &src) {
    if (this == &src) return *this;
    _value = src._value;
    _status = src._status;
    return *this;
  }

  bool ok() const { return _status.ok(); }
  T value() const { return _value; }
  Status status() const { return _status; }

 private:
  T _value;
  Status _status;
};

}  // namespace error

#endif