#ifndef NET_HTTP_CGI_PAGES_PHYSICAL_PATH_CHECKER_HPP
#define NET_HTTP_CGI_PAGES_PHYSICAL_PATH_CHECKER_HPP

#include "../../system/SystemCalls.hpp"
#include "PhysicalPathChecker.hpp"

class CGIPagesPhysicalPathChecker : public PhysicalPathChecker {
 public:
  CGIPagesPhysicalPathChecker();
  ~CGIPagesPhysicalPathChecker();
  CGIPagesPhysicalPathChecker(const CGIPagesPhysicalPathChecker &src);
  CGIPagesPhysicalPathChecker &operator=(
      const CGIPagesPhysicalPathChecker &src);

  HTTPStatus::Status isThePathValidForTheGetMethod(
      const std::string &physicalPathToResource,
      bool canListDirectoryIfPathPointsToADirectory);

  HTTPStatus::Status isThePathValidForThePostMethod(
      const std::string &physicalPathToResource);

  HTTPStatus::Status isThePathValidForTheDeleteMethod(
      const std::string &physicalPathToResource);

  void setSystemCalls(SystemCalls *systemCalls);

 private:
  void freeThings();

  SystemCalls *_systemCalls;
};

#endif