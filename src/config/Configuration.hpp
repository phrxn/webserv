#ifndef CONFIG_CONFIGURATION_HPP
#define CONFIG_CONFIGURATION_HPP

#include "Variables.hpp"

class Configuration {
 public:
  Configuration();
  ~Configuration();
  Configuration(const Configuration &src);
  Configuration &operator=(const Configuration &src);

  TypesOfProtocol getTypeOfProtocol() const;
  void setTypeOfProtocol(TypesOfProtocol typeOfProtocol);

  Environment getEnvironment() const;
  void setEnvironment(Environment environment);

  int getTimeOutForNewRequestOrToSendAFullRequest() const;
  void setTimeOutForNewRequestOrToSendAFullRequest(int timeout);

 private:
  TypesOfProtocol _typeOfProtocol;
  Environment _environment;
  int _timeOutForNewRequestOrToSendAFullRequest;

};

#endif