#include "LogWriter.hpp"

#include <sstream>

LogWriter::LogWriter() : _time(new Time) {}

LogWriter::LogWriter(Time* time) : _time(time) {}

LogWriter::~LogWriter() {
  if (_time) delete _time;
}

LogWriter::LogWriter(const LogWriter& src) { *this = src; }

LogWriter& LogWriter::operator=(const LogWriter& src) {
  if (this == &src) return *this;
  if (_time != NULL) delete _time;
  _time = new Time(*src._time);
  return *this;
}

void LogWriter::log(LogLevel level, const std::string& clazzName,
                    const std::string& methodName, const std::string& message,
                    const std::string& details) {
  std::stringstream logMessage;

  logMessage << createLogStringWithoutContext(level, clazzName, methodName,
                                              message);

  if (!details.empty()) {
    logMessage << " (" << details << ")";
  }

  logMessage << std::endl;

  try {
    writeLog(logMessage.str());
  } catch (const std::exception& e) {
    /** it's the log... */
  }
}

void LogWriter::log(LogLevel level, const std::string& clazzName,
                    const std::string& methodName, const std::string& message,
                    int details) {
  std::stringstream logMessage;

  logMessage << createLogStringWithoutContext(level, clazzName, methodName,
                                              message);
  logMessage << " (" << details << ")" << std::endl;

  try {
    writeLog(logMessage.str());
  } catch (const std::exception& e) {
    /** it's the log... */
  }
}

std::string LogWriter::logToString(LogLevel level) {
  switch (level) {
    case DEBUG:
      return "DEBUG";
      break;
    case INFO:
      return "INFO";
      break;
    case WARNING:
      return "WARNING";
      break;
    case ERROR:
      return "ERROR";
      break;
    case FATAL:
      return "FATAL";
      break;
    default:
      return "---";
  }
}

std::string LogWriter::createLogStringWithoutContext(
    LogLevel level, const std::string& clazzName, const std::string& methodName,
    const std::string& message) {
  std::stringstream logMessage;

  logMessage << "[" << _time->getTimeToLog() << "] "
             << "[" << getLogLevelString(level) << "] "
             << "[" << clazzName << "] "
             << "[" << methodName << "] " << message;
  return logMessage.str();
}