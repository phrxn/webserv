#include "CGIEnvironmentVariables.hpp"

CGIEnvironmentVariables::CGIEnvironmentVariables()
    : _cgiCreateEnvironmentVariables("", ""),
      _httpRequest(NULL),
      _programConfiguration(ProgramConfiguration::getInstance()) {}

CGIEnvironmentVariables::CGIEnvironmentVariables(
    const std::string &physicalPathToResource,
    const std::string &rootVirtualHostLocation, const HTTPRequest *httpRequest)
    : _cgiCreateEnvironmentVariables(physicalPathToResource,
                                     rootVirtualHostLocation),
      _httpRequest(httpRequest),
      _programConfiguration(ProgramConfiguration::getInstance()) {}

CGIEnvironmentVariables::CGIEnvironmentVariables(
    const std::string &physicalPathToResource,
    const std::string &rootVirtualHostLocation, const HTTPRequest *httpRequest,
    ProgramConfiguration programConfiguration)
    : _cgiCreateEnvironmentVariables(physicalPathToResource,
                                     rootVirtualHostLocation),
      _httpRequest(httpRequest),
      _programConfiguration(programConfiguration) {}

CGIEnvironmentVariables::~CGIEnvironmentVariables() {}

CGIEnvironmentVariables::CGIEnvironmentVariables(
    const CGIEnvironmentVariables &src)
    : _env(src._env),
      _cgiCreateEnvironmentVariables(src._cgiCreateEnvironmentVariables),
      _httpRequest(src._httpRequest),
      _programConfiguration(src._programConfiguration) {}

CGIEnvironmentVariables &CGIEnvironmentVariables::operator=(
    const CGIEnvironmentVariables &src) {
  if (this == &src) {
    return *this;
  }

  _env = src._env;
  _cgiCreateEnvironmentVariables = src._cgiCreateEnvironmentVariables;
  _httpRequest = src._httpRequest;
  _programConfiguration = src._programConfiguration;

  return *this;
}

char **CGIEnvironmentVariables::createEnvironmentVariables() {
  if (_programConfiguration.getEnvironmentVariables()) {
    _env.addVariables(_programConfiguration.getEnvironmentVariables());
  }
  _cgiCreateEnvironmentVariables.setProgramConfiguration(_programConfiguration);
  if (_httpRequest) {
    _env.addVariables(
        _cgiCreateEnvironmentVariables.createCGIVariables(_httpRequest));
  }

  return _env.createEnvironmentVariables();
}