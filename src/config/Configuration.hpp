#ifndef CONFIG_CONFIGURATION_HPP
#define CONFIG_CONFIGURATION_HPP

#include <list>

#include "Variables.hpp"
#include "../error/Log.hpp"
#include "../net/http/HTTPv1_1_Methods.hpp"

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

  bool theServerSupportsThisHTTPMethod(HTTPv1_1_Methods method);

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
  std::list<HTTPv1_1_Methods> _listSupportedMethods;

};

#endif