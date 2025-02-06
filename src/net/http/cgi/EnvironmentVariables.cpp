#include "EnvironmentVariables.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>

const std::string EnvironmentVariables::VARIABLE_AND_VALEU_SEPARATOR = "=";

EnvironmentVariables::EnvironmentVariables() {}

EnvironmentVariables::~EnvironmentVariables() {}

EnvironmentVariables::EnvironmentVariables(const EnvironmentVariables &src) {
  *this = src;
}

EnvironmentVariables &EnvironmentVariables::operator=(
    const EnvironmentVariables &src) {
  if (this == &src) return *this;
  _env = src._env;
  return *this;
}

const std::map<std::string, std::string> &EnvironmentVariables::getEnvMap()
    const {
  return _env;
}

std::size_t EnvironmentVariables::getEnvironmentVariablesSize(
    char **env) const {
  std::size_t count = 0;
  while (env[count]) count++;

  return count;
}

void EnvironmentVariables::addVariable(const std::string &name,
                                       const std::string &value) {
  _env[name] = value;
}

void EnvironmentVariables::addVariables(
    const std::map<std::string, std::string> &values) {
  _env.insert(values.begin(), values.end());
}

void EnvironmentVariables::addVariables(const char **environment) {
  std::size_t count = 0;

  while (environment[count] != NULL) {
    std::pair<std::string, std::string> thePair =
        createParFromStringVariable(environment[count]);
    _env.insert(thePair);
    count++;
  }
}

char **EnvironmentVariables::createEnvironmentVariables() {

  char **env = new char *[_env.size() + 1];
  env[_env.size()] = NULL;

  std::size_t count = 0;

  std::map<std::string, std::string>::const_iterator it = _env.begin();
  for (; it != _env.end(); ++it) {
    std::string tmpString;

    tmpString = it->first + VARIABLE_AND_VALEU_SEPARATOR + it->second;

    char *theString = new char[tmpString.length() + 1];
    strcpy(theString, tmpString.c_str());

    env[count] = theString;
	count++;
  }
  return env;
}

std::pair<std::string, std::string>
EnvironmentVariables::createParFromStringVariable(
    const std::string &environmentVariable) {
  std::string::size_type separator =
      environmentVariable.find(VARIABLE_AND_VALEU_SEPARATOR);
  std::string::size_type start = 0;

  std::string name = environmentVariable;
  if (separator != std::string::npos) {
    name = environmentVariable.substr(start, separator);
    start = separator + 1;
  }

  std::string value;
  if (separator != std::string::npos) {
    value = environmentVariable.substr(start);
  }

  return std::pair<std::string, std::string>(name, value);
}

std::ostream &operator<<(std::ostream &os, const EnvironmentVariables &env) {
  os << "[EnvironmentVariables: ";

  std::map<std::string, std::string>::const_iterator itBegin =
      env.getEnvMap().begin();
  std::map<std::string, std::string>::const_iterator itEnd =
      env.getEnvMap().end();

  for (; itBegin != itEnd; ++itBegin) {
    os << "[" << itBegin->first << "=" << itBegin->second << "]";
    if ((++itBegin) != itEnd) {
      os << ", ";
	  --itBegin;
    }
  }

  os << "]";

  return os;
}