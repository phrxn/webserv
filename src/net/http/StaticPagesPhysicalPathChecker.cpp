#include "StaticPagesPhysicalPathChecker.hpp"

#include <sys/stat.h>
#include <unistd.h>

StaticPagesPhysicalPathChecker::StaticPagesPhysicalPathChecker()
    : _systemCalls(new SystemCalls) {}

StaticPagesPhysicalPathChecker::~StaticPagesPhysicalPathChecker() {
  freeThings();
}

StaticPagesPhysicalPathChecker::StaticPagesPhysicalPathChecker(
    const StaticPagesPhysicalPathChecker &src)
    : _systemCalls(new SystemCalls(*src._systemCalls)) {}

StaticPagesPhysicalPathChecker &StaticPagesPhysicalPathChecker::operator=(
    const StaticPagesPhysicalPathChecker &src) {
  if (this == &src) {
    return *this;
  }
  freeThings();
  _systemCalls = new SystemCalls(*src._systemCalls);
  return *this;
}

HTTPStatus::Status
StaticPagesPhysicalPathChecker::isThePathValidForTheGetMethod(
    const std::string &physicalPathToResource,
    bool canListDirectoryIfPathPointsToADirectory) {
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

  if (S_ISDIR(info.st_mode)) {
    if (!physicalPathToResource.empty() &&
        physicalPathToResource[physicalPathToResource.size() - 1] != '/') {
      return HTTPStatus::MOVED_PERMANENTLY;
    }
    if (!canListDirectoryIfPathPointsToADirectory) {
      return HTTPStatus::FORBIDDEN;
    }
  }
  return HTTPStatus::OK;
}

HTTPStatus::Status
StaticPagesPhysicalPathChecker::isThePathValidForThePostMethod(
    const std::string &physicalPathToResource) {
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

  if (S_ISDIR(info.st_mode)) {
    if (!physicalPathToResource.empty() &&
        physicalPathToResource[physicalPathToResource.size() - 1] != '/') {
      return HTTPStatus::MOVED_PERMANENTLY;
    }
    return HTTPStatus::FORBIDDEN;
  }

  return HTTPStatus::NOT_ALLOWED;
}

HTTPStatus::Status
StaticPagesPhysicalPathChecker::isThePathValidForTheDeleteMethod(
    const std::string &physicalPathToResource) {
  (void)physicalPathToResource;
  return HTTPStatus::NOT_ALLOWED;
}

error::StatusOr<bool>
StaticPagesPhysicalPathChecker::isThePathAPathToADirectory(
    const std::string &physicalPathToResource) {
  struct stat info;

  error::StatusOr<int> statWasFilledIn =
      _systemCalls->stat(physicalPathToResource.c_str(), &info);

  if (!statWasFilledIn.ok()) {
    return statWasFilledIn.status();
  }

  if (S_ISDIR(info.st_mode)) {
    return true;
  }
  return false;
}

void StaticPagesPhysicalPathChecker::setSystemCalls(SystemCalls *systemCalls) {
  if (_systemCalls) {
    delete _systemCalls;
  }
  _systemCalls = systemCalls;
}

void StaticPagesPhysicalPathChecker::freeThings() {
  if (_systemCalls) {
    delete _systemCalls;
  }
}