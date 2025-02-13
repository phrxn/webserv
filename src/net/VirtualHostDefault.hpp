#ifndef NET_VIRTUAL_HOST_DEFAULT_HPP
#define NET_VIRTUAL_HOST_DEFAULT_HPP

#include <string>
#include "URL.hpp"
#include "http/HTTPMethods.hpp"
#include "http/HTTPStatus.hpp"
#include "VirtualHost.hpp"

class VirtualHostDefault : public VirtualHost{
 public:
  VirtualHostDefault();
  VirtualHostDefault(int port, const std::string &serverName);
  ~VirtualHostDefault();
  VirtualHostDefault(const VirtualHostDefault &src);
  VirtualHostDefault &operator=(const VirtualHostDefault &src);
  bool operator==(const VirtualHostDefault &src) const;

  unsigned int getPort() const;
  void setPort(unsigned int port);
  std::string getServerName() const;
  void setServerName(const std::string &serverName);

  bool isPathValid(const URL& url) const;
  std::string isPathARedirection(const URL& url) const;
  bool isTheMethodAllowedForThisPath(const URL& url, HTTPMethods::Method method) const;
  bool isUrlAPathToCGI(const URL& url) const;
  std::string getThePhysicalPath(const URL& url) const;
  bool isDirectoryListingAllowedForThisPath(const URL& url) const;
  std::string getThePathToCustomPageForHTTPStatus(HTTPStatus::Status httpStatus) const;

 private:
  unsigned int _port;
  std::string _serverName;
};

#endif