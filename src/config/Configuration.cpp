#include "Configuration.hpp"

#include <algorithm>
#include <stdexcept>

Configuration::Configuration()
    : _typeOfProtocol(HTTP),
      _environment(TEST),
      _timeOutForNewRequestOrToSendAFullRequest(10) {
  // If the singleton is being respected, the list should only be filled out
  // once
  if (!_listSupportedMethods.empty())
    throw std::runtime_error("the list of supported methods is greater than 0");

  _listSupportedMethods.push_back(HTTPMethods::GET);
  _listSupportedMethods.push_back(HTTPMethods::POST);
  _listSupportedMethods.push_back(HTTPMethods::DELETE);
}

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

Configuration &Configuration::getInstance() {
  static Configuration instance;
  return instance;
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

bool Configuration::theServerSupportsThisHTTPMethod(HTTPMethods::Method method) {
  std::list<HTTPMethods::Method>::iterator it = std::find(
      _listSupportedMethods.begin(), _listSupportedMethods.end(), method);
  return (it != _listSupportedMethods.end());
}