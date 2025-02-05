#ifndef NET_VIRTUAL_HOST_HPP
#define NET_VIRTUAL_HOST_HPP

#include <string>
#include "URL.hpp"
#include "http/HTTPMethods.hpp"
#include "http/HTTPStatus.hpp"

class VirtualHost {
 public:

  virtual ~VirtualHost();

  virtual int getPort() const = 0;
  virtual void setPort(int port) = 0;
  virtual std::string getServername() const = 0;
  virtual void setServername(const std::string &serverName) = 0;

  virtual bool isPathValid(URL url) const = 0;
  virtual std::string isPathARedirection(URL url) const = 0;
  virtual bool isTheMethodAllowedForThisPath(URL url, HTTPMethods::Method method) const = 0;
  virtual bool isUrlAPathToCGI(URL url) const = 0;
  virtual std::string getThePhysicalPath(URL url) const = 0;
  virtual bool isDirectoryListingAllowedForThisPath(URL url) const = 0;
  virtual std::string getThePathToCustomPageForHTTPStatus(HTTPStatus::Status httpStatus) const = 0;
};

#endif