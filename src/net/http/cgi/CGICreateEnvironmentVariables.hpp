#ifndef NET_HTTP_CGI_CGI_CREATE_ENVIRONMENT_VARIABLES_HPP
#define NET_HTTP_CGI_CGI_CREATE_ENVIRONMENT_VARIABLES_HPP

#include <map>
#include <string>

#include "../../../config/ProgramConfiguration.hpp"
#include "../../SocketFileDescriptor.hpp"
#include "../../VirtualHost.hpp"
#include "../HTTPRequest.hpp"
#include "../HTTPMethods.hpp"

class CGICreateEnvironmentVariables {
 public:
  CGICreateEnvironmentVariables(const std::string &physicalPathToResource, const std::string &rootVirtualHostLocation);
  ~CGICreateEnvironmentVariables();
  CGICreateEnvironmentVariables(const CGICreateEnvironmentVariables &src);
  CGICreateEnvironmentVariables &operator=(const CGICreateEnvironmentVariables &src);
  bool operator==(const CGICreateEnvironmentVariables &src) const;

  std::map<std::string, std::string> createCGIVariables(HTTPRequest *hTTPRequest);

  std::string methodToString(HTTPMethods::Method method) const;
  std::string extractScriptPath(const URL &url,
                                const std::string &scriptExtesion) const;
  std::string extractExtraPath(const URL &url,
                               const std::string &scriptExtesion) const;

  std::string getServerPort(int serverPort) const;

  void setProgramConfiguration(const ProgramConfiguration &configuration);

  std::string getPhysicalPathToResource() const;
  std::string getRootVirtualHostLocation() const;

 private:
  std::string _physicalPathToResource;
  std::string _rootVirtualHostLocation;
  ProgramConfiguration _configuration;
  HTTPMethods _httpMethods;
  std::map<std::string, std::string> _mapVariables;

};

std::ostream &operator<<(std::ostream &os, const std::map<std::string, std::string> &mapVariables);

#endif
