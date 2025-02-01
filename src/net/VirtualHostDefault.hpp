#ifndef NET_VIRTUAL_HOST_DEFAULT_HPP
#define NET_VIRTUAL_HOST_DEFAULT_HPP

#include <string>
#include "URL.hpp"
#include "http/HTTPMethods.hpp"
#include "http/HTTPStatus.hpp"

class VirtualHostDefault {
 public:
  VirtualHostDefault();
  VirtualHostDefault(int port, const std::string &serverName);
  virtual ~VirtualHostDefault();
  VirtualHostDefault(const VirtualHostDefault &src);
  VirtualHostDefault &operator=(const VirtualHostDefault &src);
  bool operator==(const VirtualHostDefault &src) const;


  virtual int getPort() const;
  virtual void setPort(int port);
  virtual std::string getServername() const;
  virtual void setServername(const std::string &serverName);

  virtual bool isPathValid(URL url) const;
  virtual std::string isPathARedirection(URL url) const;
  virtual bool isTheMethodAllowedForThisPath(URL url, HTTPMethods::Method method) const;
  virtual bool isUrlAPathToCGI(URL url) const;
  virtual std::string getThePhysicalPath(URL url) const;
  virtual bool isDirectoryListingAllowedForThisPath(URL url) const;
  virtual std::string getThePathToCustomPageForHTTPStatus(HTTPStatus::Status httpStatus) const;

 private:
  int _port;
  std::string _serverName;
};

#endif