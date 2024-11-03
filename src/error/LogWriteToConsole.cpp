#include "LogWriteToConsole.hpp"

#include <iostream>
#include <sstream>

LogWriteToConsole::LogWriteToConsole() {}

LogWriteToConsole::~LogWriteToConsole() {}

LogWriteToConsole::LogWriteToConsole(const LogWriteToConsole &src)
    : LogWriter(src) {
  *this = src;
}

LogWriteToConsole &LogWriteToConsole::operator=(const LogWriteToConsole &src) {
  (void)src;
  return *this;
}

void LogWriteToConsole::writeLog(const std::string &formattedLog) {
  std::cout << formattedLog << std::flush;
}

std::string LogWriteToConsole::getLogLevelString(LogLevel level) {
  std::stringstream logLevelString;

  std::string color;
  std::string resetColor("\033[0m");

  switch (level) {
    case DEBUG:
      color = "\033[34m";
      break;
    case INFO:
      color = "\033[32m";
      break;
    case WARNING:
      color = "\033[33m";
      break;
    case ERROR:
      color = "\033[31m";
      break;
    case FATAL:
      color = "\033[35m";
      break;
  }

  logLevelString << color << LogWriter::logToString(level) << resetColor;

  return logLevelString.str();
}