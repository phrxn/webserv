#ifndef ERROR_LOG_DEFAULT_HPP
#define ERROR_LOG_DEFAULT_HPP

#include <list>

#include "Log.hpp"

class LogDefault : public Log {
 public:
  LogDefault();
  ~LogDefault();

  void log(LogLevel level, const std::string &clazzName,
           const std::string &methodName, const std::string &message,
           const std::string &details);

  void log(LogLevel level, const std::string &clazzName,
           const std::string &methodName, const std::string &message,
           int details);

  void startLogger();

 private:
  LogDefault(const LogDefault &src);

  void clearListLogListerns();

  LogDefault &operator=(const LogDefault &src);

  std::list<Log *> _listLogListeners;
};

#endif