#ifndef NET_HTTP_CGI_CGI_CREATE_ENVIRONMENT_VARIABLES_HPP
#define NET_HTTP_CGI_CGI_CREATE_ENVIRONMENT_VARIABLES_HPP

#include <map>
#include <string>

#include "../../../config/Configuration.hpp"
#include "../../SocketFileDescriptor.hpp"
#include "../../VirtualHost.hpp"
#include "../HTTPRequest.hpp"

class CGICreateEnvironmentVariables {
 public:
  CGICreateEnvironmentVariables();
  ~CGICreateEnvironmentVariables();

  std::map<std::string, std::string> createCGIVariables(
      const SocketFileDescriptor *_socketFD, const VirtualHost *_virtualHost,
      const HTTPRequest *_hTTPRequest, const Configuration &_configuration);

  std::string methodToString(HTTPMethods::Method method) const;
  std::string extractScriptPath(const URL &url,
                                const std::string &scriptExtesion) const;
  std::string extractExtraPath(const URL &url,
                               const std::string &scriptExtesion) const;

  std::string getServerPort(int serverPort) const;

 private:
  CGICreateEnvironmentVariables(const CGICreateEnvironmentVariables &src);
  CGICreateEnvironmentVariables &operator=(CGICreateEnvironmentVariables &src);

  const SocketFileDescriptor *_socketFD;
  const VirtualHost *_virtualHost;
  const HTTPRequest *_hTTPRequest;
  const Configuration &_configuration;
};

#endif
