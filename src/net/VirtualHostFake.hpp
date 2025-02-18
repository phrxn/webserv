#ifndef NET_VIRTUAL_HOST_FAKE_HPP
#define NET_VIRTUAL_HOST_FAKE_HPP

#include <string>
#include "URL.hpp"
#include "http/HTTPMethods.hpp"
#include "http/HTTPStatus.hpp"
#include "VirtualHostDefault.hpp"

class VirtualHostFake : public VirtualHostDefault{
 public:
  VirtualHostFake();
  VirtualHostFake(int port, const std::string &serverName);
  ~VirtualHostFake();
  VirtualHostFake(const VirtualHostFake &src);
  VirtualHostFake &operator=(const VirtualHostFake &src);

  bool isPathValid(const URL& url) const;
  std::string isPathARedirection(const URL& url) const;
  bool isTheMethodAllowedForThisPath(const URL& url, HTTPMethods::Method method) const;
  bool isUrlAPathToCGI(const URL& url) const;
  std::string getThePhysicalPath(const URL& url) const;
  std::string getTheRelativePhysicalPath(const URL& url) const;
  bool isDirectoryListingAllowedForThisPath(const URL& url) const;
  std::string getThePathToCustomPageForHTTPStatus(HTTPStatus::Status httpStatus) const;
  std::string getRootDir(const URL& url) const;
  std::string getIndexFile(const URL& url) const;
  size_t getLimitBodySizeInBytes(void) const;

  // Return the upload folder full path
  //
  // a empty string is returned if the upload folder is not set
  // or the path points to a CGI
  std::string getUploadFolderPath(const URL& url) const;


};

#endif