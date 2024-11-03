#include "LogDefault.hpp"

#include "LogWriteToConsole.hpp"

LogDefault::LogDefault() {}

LogDefault ::~LogDefault() { clearListLogListerns(); }

// private (this class MUST BE UNIQUE!)
LogDefault ::LogDefault(const LogDefault &src) { *this = src; }

// private (this class MUST BE UNIQUE!)
LogDefault &LogDefault::operator=(const LogDefault &src) {
  if (this == &src) return *this;
  return *this;
}

void LogDefault::log(LogLevel level, const std::string &clazzName,
                     const std::string &methodName, const std::string &message,
                     const std::string &details) {
  for (std::list<Log *>::iterator it = _listLogListeners.begin();
       it != _listLogListeners.end(); ++it) {
    try {
      (*it)->log(level, clazzName, methodName, message, details);
    } catch (const std::exception &e) {
      /** it's the log... */
    }
  }
}

void LogDefault::log(LogLevel level, const std::string &clazzName,
                     const std::string &methodName, const std::string &message,
                     int details) {
  for (std::list<Log *>::iterator it = _listLogListeners.begin();
       it != _listLogListeners.end(); ++it) {
    try {
      (*it)->log(level, clazzName, methodName, message, details);
    } catch (const std::exception &e) {
      /** it's the log... */
    }
  }
}

void LogDefault::startLogger() {
  LogWriteToConsole *logWriteToConsole = new LogWriteToConsole;

  _listLogListeners.push_back(logWriteToConsole);
}

void LogDefault::clearListLogListerns() {
  for (std::list<Log *>::iterator it = _listLogListeners.begin();
       it != _listLogListeners.end(); ++it) {
    delete *it;
  }
  _listLogListeners.clear();
}
