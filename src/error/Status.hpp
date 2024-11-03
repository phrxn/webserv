#ifndef ERROR_STATUS_HPP
#define ERROR_STATUS_HPP

#include <string>

namespace error {
class Status {
 public:
  enum Code { OK = 0, SystemCall };

  Status();
  Status(Code code);
  Status(Code code, const std::string &message);
  Status(const Status &src);
  ~Status();
  Status &operator=(const Status &src);

  bool ok() const;
  Code code() const;
  std::string message() const;

 private:
  Code _code;
  std::string _message;
};
}  // namespace error
#endif