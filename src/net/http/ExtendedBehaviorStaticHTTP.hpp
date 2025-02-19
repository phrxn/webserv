#ifndef NET_HTTP_EXTENDED_BEHAVIOR_STATIC_HTTP_HPP
#define NET_HTTP_EXTENDED_BEHAVIOR_STATIC_HTTP_HPP

#include "HTTPStatus.hpp"
#include "HTTPRequest.hpp"

#include "../../system/SystemCalls.hpp"

class ExtendedBehaviorStaticHTTP
{
  public:
	ExtendedBehaviorStaticHTTP();
	~ExtendedBehaviorStaticHTTP();
	ExtendedBehaviorStaticHTTP(const ExtendedBehaviorStaticHTTP &src);
	ExtendedBehaviorStaticHTTP &operator=(const ExtendedBehaviorStaticHTTP &src);

	HTTPStatus::Status doPost(const std::string &physicalRelativePath, const std::string &uploadFolder, HTTPRequest &request);

	HTTPStatus::Status doDelete(const std::string &physicalPathToResource);

	HTTPStatus::Status isFullPhysicalUploadPathValid(const std::string &fullPhysicalUploadPath);

	bool pathEndsWithSlash(const std::string &pathToResource);
	std::string getParentDir(const std::string &pathToFile);
	HTTPStatus::Status isParentDirValid(const std::string &parentDir);

  private:
    SystemCalls _systemCalls;
};

#endif