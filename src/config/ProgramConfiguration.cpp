#include "ProgramConfiguration.hpp"

#include <algorithm>
#include <stdexcept>

ProgramConfiguration::ProgramConfiguration()
    : _typeOfProtocol(HTTP),
      _environment(TEST),
      _timeOutForNewRequestOrToSendAFullRequest(10) {
  // If the singleton is being respected, the list should only be filled out
  // once
  if (!_listSupportedMethodsByServer.empty())
    throw std::runtime_error("the list of supported methods is greater than 0");

  _listSupportedMethodsByServer.push_back(HTTPMethods::GET);
  _listSupportedMethodsByServer.push_back(HTTPMethods::POST);
  _listSupportedMethodsByServer.push_back(HTTPMethods::DELETE);
}

ProgramConfiguration::~ProgramConfiguration() {}

ProgramConfiguration::ProgramConfiguration(const ProgramConfiguration &src) { *this = src; }

ProgramConfiguration &ProgramConfiguration::operator=(const ProgramConfiguration &src) {
  if (this == &src) return *this;
  _typeOfProtocol = src._typeOfProtocol;
  _environment = src._environment;
  _timeOutForNewRequestOrToSendAFullRequest =
      src._timeOutForNewRequestOrToSendAFullRequest;
  _logLevel = src._logLevel;
  return *this;
}

ProgramConfiguration &ProgramConfiguration::getInstance() {
  static ProgramConfiguration instance;
  return instance;
}

TypesOfProtocol ProgramConfiguration::getTypeOfProtocol() const {
  return _typeOfProtocol;
}
void ProgramConfiguration::setTypeOfProtocol(TypesOfProtocol typeOfProtocol) {
  _typeOfProtocol = typeOfProtocol;
}

Environment ProgramConfiguration::getEnvironment() const { return _environment; }

void ProgramConfiguration::setEnvironment(Environment environment) {
  _environment = environment;
}

int ProgramConfiguration::getTimeOutForNewRequestOrToSendAFullRequest() const {
  return _timeOutForNewRequestOrToSendAFullRequest;
}

void ProgramConfiguration::setTimeOutForNewRequestOrToSendAFullRequest(int timeout) {
  _timeOutForNewRequestOrToSendAFullRequest = timeout;
}

Log::LogLevel ProgramConfiguration::getLogLevel() const { return _logLevel; }

void ProgramConfiguration::setLogLevel(Log::LogLevel logLevel) {
  _logLevel = logLevel;
}

bool ProgramConfiguration::theServerSupportsThisHTTPMethod(
    HTTPMethods::Method method) {
  std::list<HTTPMethods::Method>::iterator it =
      std::find(_listSupportedMethodsByServer.begin(),
                _listSupportedMethodsByServer.end(), method);
  return (it != _listSupportedMethodsByServer.end());
}

const char **ProgramConfiguration::getEnvironmentVariables() const {
  return _environmentVariables;
}

void ProgramConfiguration::setEnvironmentVariables(
    const char **environmentVariables) {
  _environmentVariables = environmentVariables;
}