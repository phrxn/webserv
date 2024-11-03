#ifndef ERROR_LOG_HPP
#define ERROR_LOG_HPP

#include <string>

class Log {
 public:
  enum LogLevel { DEBUG, INFO, WARNING, ERROR, FATAL };

  virtual ~Log();

  virtual void log(LogLevel level, const std::string &clazzName,
                   const std::string &methodName, const std::string &message,
                   const std::string &details) = 0;

  virtual void log(LogLevel level, const std::string &clazzName,
                   const std::string &methodName, const std::string &message,
                   int details) = 0;
};

#endif