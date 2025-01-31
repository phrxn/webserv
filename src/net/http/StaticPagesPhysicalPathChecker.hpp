#ifndef NET_HTTP_STATIC_PAGES_PHYSICAL_PATH_CHECKER_HPP
#define NET_HTTP_STATIC_PAGES_PHYSICAL_PATH_CHECKER_HPP

#include "../../system/SystemCalls.hpp"
#include "PhysicalPathChecker.hpp"

class StaticPagesPhysicalPathChecker : public PhysicalPathChecker {
 public:
  StaticPagesPhysicalPathChecker();
  ~StaticPagesPhysicalPathChecker();
  StaticPagesPhysicalPathChecker(const StaticPagesPhysicalPathChecker &src);
  StaticPagesPhysicalPathChecker &operator=(
      const StaticPagesPhysicalPathChecker &src);

  HTTPStatus::Status isThePathValidForTheGetMethod(
      const std::string &physicalPathToResource,
      bool canListDirectoryIfPathPointsToADirectory);

  HTTPStatus::Status isThePathValidForThePostMethod(
      const std::string &physicalPathToResource);

  HTTPStatus::Status isThePathValidForTheDeleteMethod(
      const std::string &physicalPathToResource);

  error::StatusOr<bool> isThePathAPathToADirectory(
      const std::string &physicalPathToResource);

  void setSystemCalls(SystemCalls *systemCalls);

 private:
  void freeThings();

  SystemCalls *_systemCalls;
};

#endif