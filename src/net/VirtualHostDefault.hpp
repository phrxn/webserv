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

  int getPort() const;
  void setPort(int port);
  std::string getServername() const;
  void setServername(const std::string &serverName);

  bool isPathValid(URL url) const;
  std::string isPathARedirection(URL url) const;
  bool isTheMethodAllowedForThisPath(URL url, HTTPMethods::Method method) const;
  bool isUrlAPathToCGI(URL url) const;
  std::string getThePhysicalPath(URL url) const;
  bool isDirectoryListingAllowedForThisPath(URL url) const;
  std::string getThePathToCustomPageForHTTPStatus(HTTPStatus::Status httpStatus) const;

 private:
  int _port;
  std::string _serverName;
};

#endif