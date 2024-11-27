#ifndef CONFIG_CONFIGURATION_HPP
#define CONFIG_CONFIGURATION_HPP

#include "Variables.hpp"

class Configuration {
 public:
  Configuration();
  ~Configuration();
  Configuration(const Configuration &src);
  Configuration &operator=(const Configuration &src);

  TypesOfProtocol getTypeOfProtocol();
  void setTypeOfProtocol(TypesOfProtocol typeOfProtocol);

  Environment getEnvironment();
  void setEnvironment(Environment environment);

 private:
  TypesOfProtocol _typeOfProtocol;
  Environment _environment;

};

#endif