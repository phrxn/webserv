#ifndef ERROR_LOG_WRITE_ON_CONSOLE_HPP
#define ERROR_LOG_WRITE_ON_CONSOLE_HPP

#include "LogWriter.hpp"

class LogWriteToConsole : public LogWriter {
 public:
  LogWriteToConsole();
  ~LogWriteToConsole();
  LogWriteToConsole(const LogWriteToConsole &src);

  LogWriteToConsole &operator=(const LogWriteToConsole &src);

  void writeLog(const std::string &formattedLog);

  std::string getLogLevelString(LogLevel level);

  std::string getDetailsFormatted(LogLevel level, const std::string &details);
  std::string getDetailsFormatted(LogLevel level, int details);

 private:
  std::string getColorByLevel(LogLevel level);
  std::string getResetColor();
};

#endif