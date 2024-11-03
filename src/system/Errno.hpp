#ifndef SYSTEM_ERRNO_HPP
#define SYSTEM_ERRNO_HPP

#include <string>

class Errno {
 public:
  Errno();
  Errno(const Errno &src);
  virtual ~Errno();

  Errno &operator=(const Errno &src);

  virtual std::string getErrorMessage() const;
};

#endif