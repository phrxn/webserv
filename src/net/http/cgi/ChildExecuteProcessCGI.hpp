#ifndef NET_HTTP_CGI_CHILD_EXECUTE_PROCESS_CGI_HPP
#define NET_HTTP_CGI_CHILD_EXECUTE_PROCESS_CGI_HPP

#include "ArrayChar.hpp"
#include "CGIEnvironmentVariables.hpp"
#include "ExecuteProcessCGI.hpp"
#include "FilesToCGI.hpp"

class ChildExecuteProcessCGI : public ExecuteProcessCGI {
 public:
  ChildExecuteProcessCGI(const ArrayChar &cgiPath,
                         const CGIEnvironmentVariables &cgiEnvironmentVariables,
                        FilesToCGI &filesToCGI);
  ~ChildExecuteProcessCGI();
  ChildExecuteProcessCGI(const ChildExecuteProcessCGI &src);
  ChildExecuteProcessCGI &operator=(const ChildExecuteProcessCGI &src);
  ExitStatus execute();
  void setSystemCalls(SystemCalls *systemCalls);
  void setLogger(Log *logger);


 private:
  ArrayChar _argv;
  CGIEnvironmentVariables _cgiEnvironmentVariables;
  FilesToCGI &_filesToCGI;
  SystemCalls *_systemCalls;
  Log *_logger;

};

#endif