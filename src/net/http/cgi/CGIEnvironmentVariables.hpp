#ifndef NET_HTTP_CGI_CGI_ENVIRONMENT_VARIABLES_HPP
#define NET_HTTP_CGI_CGI_ENVIRONMENT_VARIABLES_HPP

#include "EnvironmentVariables.hpp"
#include "CGICreateEnvironmentVariables.hpp"
#include "../../../config/ProgramConfiguration.hpp"

#include "../HTTPRequest.hpp"

class CGIEnvironmentVariables{

public:
  CGIEnvironmentVariables();
  CGIEnvironmentVariables(const std::string &physicalPathToResource, const std::string &rootVirtualHostLocation, HTTPRequest *httpRequest);
  CGIEnvironmentVariables(const std::string &physicalPathToResource, const std::string &rootVirtualHostLocation, HTTPRequest *httpRequest, ProgramConfiguration programConfiguration);

  ~CGIEnvironmentVariables();
  CGIEnvironmentVariables(const CGIEnvironmentVariables &src);
  CGIEnvironmentVariables &operator=(const CGIEnvironmentVariables &src);

  char **createEnvironmentVariables();

private:
	EnvironmentVariables _env;
	CGICreateEnvironmentVariables _cgiCreateEnvironmentVariables;
	HTTPRequest *_httpRequest;
	ProgramConfiguration _programConfiguration;

};

#endif
