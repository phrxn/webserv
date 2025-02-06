#include "CGIPagesPhysicalPathChecker.hpp"

#include <sys/stat.h>
#include <unistd.h>

CGIPagesPhysicalPathChecker::CGIPagesPhysicalPathChecker()
    : _systemCalls(new SystemCalls) {}

CGIPagesPhysicalPathChecker::~CGIPagesPhysicalPathChecker() { freeThings(); }

CGIPagesPhysicalPathChecker::CGIPagesPhysicalPathChecker(
    const CGIPagesPhysicalPathChecker &src)
    : _systemCalls(new SystemCalls(*src._systemCalls)) {}

CGIPagesPhysicalPathChecker &CGIPagesPhysicalPathChecker::operator=(
    const CGIPagesPhysicalPathChecker &src) {
  if (this == &src) {
    return *this;
  }
  freeThings();
  _systemCalls = new SystemCalls(*src._systemCalls);
  return *this;
}

HTTPStatus::Status CGIPagesPhysicalPathChecker::isThePathValidForTheGetMethod(
    const std::string &physicalPathToResource,
    bool canListDirectoryIfPathPointsToADirectory) {
  (void)canListDirectoryIfPathPointsToADirectory;
  struct stat info;
  std::string errorMessage;

  error::StatusOr<int> statWasFilledIn =
      _systemCalls->stat(physicalPathToResource.c_str(), &info);

  if (!statWasFilledIn.ok()) {
    errorMessage = statWasFilledIn.status().message();

    if (errorMessage.find("Not a directory") != std::string::npos ||
        errorMessage.find("No such file or directory") != std::string::npos) {
      return HTTPStatus::NOT_FOUND;
    }
    if (errorMessage.find("Permission denied") != std::string::npos) {
      return HTTPStatus::FORBIDDEN;
    }
  }

  error::StatusOr<int> isReadable =
      _systemCalls->access(physicalPathToResource.c_str(), F_OK | R_OK);

  if (!isReadable.ok()) {
    return HTTPStatus::FORBIDDEN;
  }
  return HTTPStatus::OK;
}

HTTPStatus::Status CGIPagesPhysicalPathChecker::isThePathValidForThePostMethod(
    const std::string &physicalPathToResource) {
  return isThePathValidForTheGetMethod(physicalPathToResource, false);
}

HTTPStatus::Status
CGIPagesPhysicalPathChecker::isThePathValidForTheDeleteMethod(
    const std::string &physicalPathToResource) {
  return isThePathValidForTheGetMethod(physicalPathToResource, false);
}

void CGIPagesPhysicalPathChecker::setSystemCalls(SystemCalls *systemCalls) {
  if (_systemCalls) {
    delete _systemCalls;
  }
  _systemCalls = systemCalls;
}

void CGIPagesPhysicalPathChecker::freeThings() {
  if (_systemCalls) {
    delete _systemCalls;
  }
}