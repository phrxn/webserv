#ifndef ERROR_LOG_WRITER_HPP
#define ERROR_LOG_WRITER_HPP

#include <string>

#include "../time/Time.hpp"
#include "Log.hpp"

class LogWriter : public Log {
 public:
  LogWriter();
  LogWriter(Time *time);

  virtual ~LogWriter();

  void log(LogLevel level, const std::string &clazzName,
           const std::string &methodName, const std::string &message,
           const std::string &details);

  void log(LogLevel level, const std::string &clazzName,
           const std::string &methodName, const std::string &message,
           int details);

  std::string logToString(LogLevel level);

 protected:
  LogWriter(const LogWriter &src);
  LogWriter &operator=(const LogWriter &src);

  // the implement MUST save the log string
  virtual void writeLog(const std::string &formattedLog) = 0;

  virtual std::string getLogLevelString(LogLevel level) = 0;

 private:
  std::string createLogStringWithoutContext(LogLevel level,
                                            const std::string &clazzName,
                                            const std::string &methodName,
                                            const std::string &message);

  Time *_time;
};

#endif