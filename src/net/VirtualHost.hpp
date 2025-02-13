#ifndef NET_VIRTUAL_HOST_HPP
#define NET_VIRTUAL_HOST_HPP

#include <string>
#include "URL.hpp"
#include "http/HTTPMethods.hpp"
#include "http/HTTPStatus.hpp"

class VirtualHost {
 public:

  virtual ~VirtualHost();

  virtual unsigned int getPort() const = 0;
  virtual void setPort(unsigned int port) = 0;
  virtual std::string getServerName() const = 0;
  virtual void setServerName(const std::string &serverName) = 0;

  virtual bool isPathValid(const URL& url) const = 0;
  virtual std::string isPathARedirection(const URL& url) const = 0;
  virtual bool isTheMethodAllowedForThisPath(const URL& url, HTTPMethods::Method method) const = 0;
  virtual bool isUrlAPathToCGI(const URL& url) const = 0;
  virtual std::string getThePhysicalPath(const URL& url) const = 0;
  virtual bool isDirectoryListingAllowedForThisPath(const URL& url) const = 0;
  virtual std::string getThePathToCustomPageForHTTPStatus(HTTPStatus::Status httpStatus) const = 0;

};

#endif