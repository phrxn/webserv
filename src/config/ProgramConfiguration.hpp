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

  void setListSupportedMethodsByServer(
	const std::list<HTTPMethods::Method> &listSupportedMethodsByServer);

  bool theServerSupportsThisHTTPMethod(HTTPMethods::Method method);

  const char **getEnvironmentVariables() const;
  void setEnvironmentVariables(
      const char **environmentVariables);

  std::size_t getMaxRequestSizeInBytes() const;
  void setMaxRequestSizeInBytes(std::size_t maxSize);

  std::string getServerName() const;
  void setServerName(const std::string &serverName);

  std::string getHTTPVersion() const;
  void setHTTPVersion(const std::string &httpVersion);

  std::string getCGIVersion() const;
  void setCGIVersion(const std::string &cgiVersion);

  ProgramConfiguration();
  ProgramConfiguration(const ProgramConfiguration &src);
  ProgramConfiguration &operator=(const ProgramConfiguration &src);

 protected:
  TypesOfProtocol _typeOfProtocol;
  Environment _environment;
  int _timeOutForNewRequestOrToSendAFullRequest;
  Log::LogLevel _logLevel;
  std::list<HTTPMethods::Method> _listSupportedMethodsByServer;
  const char **_environmentVariables;
  std::size_t _maxRequestSizeInBytes;
  std::string _serverName;
  std::string _httpVersion;
  std::string _cgiVersion;

};

#endif