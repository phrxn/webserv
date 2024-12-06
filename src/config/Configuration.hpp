#ifndef CONFIG_CONFIGURATION_HPP
#define CONFIG_CONFIGURATION_HPP

#include <list>

#include "Variables.hpp"
#include "../error/Log.hpp"
#include "../net/http/HTTPMethods.hpp"

class Configuration {
 public:
  static Configuration &getInstance();

  ~Configuration();

  TypesOfProtocol getTypeOfProtocol() const;
  void setTypeOfProtocol(TypesOfProtocol typeOfProtocol);

  Environment getEnvironment() const;
  void setEnvironment(Environment environment);

  int getTimeOutForNewRequestOrToSendAFullRequest() const;
  void setTimeOutForNewRequestOrToSendAFullRequest(int timeout);

  bool theServerSupportsThisHTTPMethod(HTTPMethods::Method method);

  Log::LogLevel getLogLevel() const;
  void setLogLevel(Log::LogLevel logLevel);

 protected:
  Configuration();
  Configuration(const Configuration &src);
  Configuration &operator=(const Configuration &src);

  TypesOfProtocol _typeOfProtocol;
  Environment _environment;
  int _timeOutForNewRequestOrToSendAFullRequest;
  Log::LogLevel _logLevel;
  std::list<HTTPMethods::Method> _listSupportedMethods;

};

#endif