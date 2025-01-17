#ifndef CONFIG_PROGRAM_CONFIGURATION_HPP
#define CONFIG_PROGRAM_CONFIGURATION_HPP

#include <list>

#include "../error/Log.hpp"
#include "../net/http/HTTPMethods.hpp"
#include "Variables.hpp"

class ProgramConfiguration {
 public:
  static ProgramConfiguration &getInstance();

  ~ProgramConfiguration();

  TypesOfProtocol getTypeOfProtocol() const;
  void setTypeOfProtocol(TypesOfProtocol typeOfProtocol);

  Environment getEnvironment() const;
  void setEnvironment(Environment environment);

  int getTimeOutForNewRequestOrToSendAFullRequest() const;
  void setTimeOutForNewRequestOrToSendAFullRequest(int timeout);

  Log::LogLevel getLogLevel() const;
  void setLogLevel(Log::LogLevel logLevel);

  bool theServerSupportsThisHTTPMethod(HTTPMethods::Method method);

  const char **getEnvironmentVariables() const;
  void setEnvironmentVariables(
      const char **environmentVariables);

 protected:
  ProgramConfiguration();
  ProgramConfiguration(const ProgramConfiguration &src);
  ProgramConfiguration &operator=(const ProgramConfiguration &src);

  TypesOfProtocol _typeOfProtocol;
  Environment _environment;
  int _timeOutForNewRequestOrToSendAFullRequest;
  Log::LogLevel _logLevel;
  std::list<HTTPMethods::Method> _listSupportedMethodsByServer;
  const char **_environmentVariables;
};

#endif