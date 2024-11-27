#include "Configuration.hpp"

Configuration::Configuration() {}

Configuration::~Configuration() {}

Configuration::Configuration(const Configuration &src) { *this = src; }

Configuration &Configuration::operator=(const Configuration &src) {
  if (this == &src) return *this;
  _typeOfProtocol = src._typeOfProtocol;
  _environment = src._environment;
  return *this;
}

TypesOfProtocol Configuration::getTypeOfProtocol() { return _typeOfProtocol; }
void Configuration::setTypeOfProtocol(TypesOfProtocol typeOfProtocol) {
  _typeOfProtocol = typeOfProtocol;
}

Environment Configuration::getEnvironment() { return _environment; }

void Configuration::setEnvironment(Environment environment) {
  _environment = environment;
}