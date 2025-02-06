#ifndef NET_HTTP_CGI_ENVIRONMENT_VARIABLES_HPP
#define NET_HTTP_CGI_ENVIRONMENT_VARIABLES_HPP

#include <map>
#include <string>
#include <vector>

class EnvironmentVariables {
 public:
  static const std::string VARIABLE_AND_VALEU_SEPARATOR;

  EnvironmentVariables();
  ~EnvironmentVariables();
  EnvironmentVariables(const EnvironmentVariables &src);
  EnvironmentVariables &operator=(const EnvironmentVariables &src);

  const std::map<std::string, std::string> &getEnvMap() const;

  std::size_t getEnvironmentVariablesSize(char **env) const;

  void addVariable(const std::string &name, const std::string &value);
  void addVariables(const std::map<std::string, std::string> &values);
  void addVariables(const char **environment);

  char **createEnvironmentVariables();

  std::pair<std::string, std::string> createParFromStringVariable(
      const std::string &environmentVariable);

 private:
  std::map<std::string, std::string> _env;
};

std::ostream &operator<<(std::ostream &os, const EnvironmentVariables &env);
#endif