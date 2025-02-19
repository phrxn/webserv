#include "ExtendedBehaviorStaticHTTP.hpp"

#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <cstdio>

ExtendedBehaviorStaticHTTP::ExtendedBehaviorStaticHTTP() {}

ExtendedBehaviorStaticHTTP::~ExtendedBehaviorStaticHTTP() {}

ExtendedBehaviorStaticHTTP::ExtendedBehaviorStaticHTTP(
    const ExtendedBehaviorStaticHTTP &src) {
  (void)src;
}

ExtendedBehaviorStaticHTTP &ExtendedBehaviorStaticHTTP::operator=(
    const ExtendedBehaviorStaticHTTP &src) {
  (void)src;
  return *this;
}

HTTPStatus::Status ExtendedBehaviorStaticHTTP::doPost(
    const std::string &physicalRelativePath, const std::string &uploadFolder,
    HTTPRequest &request) {

  if (pathEndsWithSlash(physicalRelativePath)) {
	return HTTPStatus::FORBIDDEN;
  }

  std::string fullPhysicalUploadPath = uploadFolder + physicalRelativePath;

  HTTPStatus::Status fullPathCheck = isFullPhysicalUploadPathValid(fullPhysicalUploadPath);

  if(fullPathCheck != HTTPStatus::OK){
	return fullPathCheck;
  }

  std::string parentDir = getParentDir(fullPhysicalUploadPath);

  HTTPStatus::Status parentDirCheck = isParentDirValid(parentDir);

  if(parentDirCheck != HTTPStatus::OK){
	return parentDirCheck;
  }

  std::ofstream outfile(fullPhysicalUploadPath.c_str(), std::ios::out | std::ios::trunc);

  if (!outfile.is_open()) {
	  return HTTPStatus::INTERNAL_SERVER_ERROR;
  }

  outfile << request.getBody();

  if (outfile.fail()) {
	 return HTTPStatus::INTERNAL_SERVER_ERROR;
  }

  outfile.close();

  return HTTPStatus::CREATED;
}

HTTPStatus::Status ExtendedBehaviorStaticHTTP::doDelete(
    const std::string &physicalPathToResource) {

	struct stat info;
	std::string errorMessage;

	error::StatusOr<int> statWasFilledIn = _systemCalls.stat(physicalPathToResource.c_str(), &info);

	if (!statWasFilledIn.ok()) {
		errorMessage = statWasFilledIn.status().message();

		if (errorMessage.find("Not a directory") != std::string::npos){
			return HTTPStatus::FORBIDDEN;
		}

		if (errorMessage.find("Permission denied") != std::string::npos) {
			return HTTPStatus::FORBIDDEN;
		}

		if (errorMessage.find("No such file or directory") != std::string::npos) {
			return HTTPStatus::NOT_FOUND;
		}
	}

	if (S_ISDIR(info.st_mode)) {
		return HTTPStatus::FORBIDDEN;
	}

	if (!std::remove(physicalPathToResource.c_str())){
		return HTTPStatus::NO_CONTENT;
	}
	return HTTPStatus::INTERNAL_SERVER_ERROR;
}

bool ExtendedBehaviorStaticHTTP::pathEndsWithSlash(const std::string &pathToResource){
	return (!pathToResource.empty() && pathToResource[pathToResource.size() - 1] == '/');
}

HTTPStatus::Status ExtendedBehaviorStaticHTTP::isFullPhysicalUploadPathValid(const std::string &fullPhysicalUploadPath) {

	struct stat info;
	std::string errorMessage;

	error::StatusOr<int> statWasFilledIn = _systemCalls.stat(fullPhysicalUploadPath.c_str(), &info);

	if (!statWasFilledIn.ok()) {
	  errorMessage = statWasFilledIn.status().message();

	  if (errorMessage.find("Not a directory") != std::string::npos){
		return HTTPStatus::FORBIDDEN;
	  }

	  if (errorMessage.find("Permission denied") != std::string::npos) {
		return HTTPStatus::FORBIDDEN;
	  }

	  if (errorMessage.find("No such file or directory") != std::string::npos) {
		return HTTPStatus::OK;
	  }

	}

	if (S_ISDIR(info.st_mode)) {
		return HTTPStatus::FORBIDDEN;
	}

	error::StatusOr<int> isWritable = _systemCalls.access(fullPhysicalUploadPath.c_str(), W_OK);

	if (!isWritable.ok()) {
		return HTTPStatus::FORBIDDEN;
	}

	return HTTPStatus::OK;
}

std::string ExtendedBehaviorStaticHTTP::getParentDir(const std::string &pathToFile){

	size_t pos = pathToFile.rfind('/');

	if (pos != std::string::npos) {
		return  pathToFile.substr(0, pos + 1);
	}
	return pathToFile;
}

HTTPStatus::Status ExtendedBehaviorStaticHTTP::isParentDirValid(const std::string &parentDir) {

  struct stat info;
  std::string errorMessage;

  error::StatusOr<int> statWasFilledIn = _systemCalls.stat(parentDir.c_str(), &info);

  if (!statWasFilledIn.ok()) {
	errorMessage = statWasFilledIn.status().message();

	if (errorMessage.find("No such file or directory") != std::string::npos) {
	  return HTTPStatus::NOT_FOUND;
	}
	if (errorMessage.find("Permission denied") != std::string::npos) {
		return HTTPStatus::FORBIDDEN;
	}
  }

  if (!S_ISDIR(info.st_mode)) {
	return HTTPStatus::FORBIDDEN;
  }

  error::StatusOr<int> isWritable = _systemCalls.access(parentDir.c_str(), W_OK | X_OK);

  if (!isWritable.ok()) {
	  return HTTPStatus::FORBIDDEN;
  }

  return HTTPStatus::OK;
}