#ifndef NET_HTTP_PHYSICAL_PATH_CHECKER_HPP
#define NET_HTTP_PHYSICAL_PATH_CHECKER_HPP

#include <string>

#include "../../error/StatusOr.hpp"
#include "HTTPStatus.hpp"

class PhysicalPathChecker {
 public:
  virtual ~PhysicalPathChecker();

  virtual HTTPStatus::Status isThePathValidForTheGetMethod(
      const std::string &physicalPathToResource,
      bool canListDirectoryIfPathPointsToADirectory) = 0;

  virtual HTTPStatus::Status isThePathValidForThePostMethod(
      const std::string &physicalPathToResource) = 0;

  virtual HTTPStatus::Status isThePathValidForTheDeleteMethod(
      const std::string &physicalPathToResource) = 0;

  virtual error::StatusOr<bool> isThePathAPathToADirectory(
      const std::string &physicalPathToResource) = 0;
};

#endif