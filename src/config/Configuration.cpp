#include "Configuration.hpp"

Configuration::Configuration()
    : _typeOfProtocol(HTTP),
      _environment(TEST),
      _timeOutForNewRequestOrToSendAFullRequest(10) {}

Configuration::~Configuration() {}

Configuration::Configuration(const Configuration &src) { *this = src; }

Configuration &Configuration::operator=(const Configuration &src) {
  if (this == &src) return *this;
  _typeOfProtocol = src._typeOfProtocol;
  _environment = src._environment;
  _timeOutForNewRequestOrToSendAFullRequest =
      src._timeOutForNewRequestOrToSendAFullRequest;
  _logLevel = src._logLevel;
  return *this;
}

TypesOfProtocol Configuration::getTypeOfProtocol() const {
  return _typeOfProtocol;
}
void Configuration::setTypeOfProtocol(TypesOfProtocol typeOfProtocol) {
  _typeOfProtocol = typeOfProtocol;
}

Environment Configuration::getEnvironment() const { return _environment; }

void Configuration::setEnvironment(Environment environment) {
  _environment = environment;
}

int Configuration::getTimeOutForNewRequestOrToSendAFullRequest() const {
  return _timeOutForNewRequestOrToSendAFullRequest;
}

void Configuration::setTimeOutForNewRequestOrToSendAFullRequest(int timeout) {
  _timeOutForNewRequestOrToSendAFullRequest = timeout;
}

Log::LogLevel Configuration::getLogLevel() const { return _logLevel; }

void Configuration::setLogLevel(Log::LogLevel logLevel) {
  _logLevel = logLevel;
}