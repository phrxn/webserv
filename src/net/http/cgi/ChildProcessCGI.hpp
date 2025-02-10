#ifndef NET_HTTP_CGI_CHILD_EXECUTE_PROCESS_CGI_HPP
#define NET_HTTP_CGI_CHILD_EXECUTE_PROCESS_CGI_HPP

#include "ArrayChar.hpp"
#include "CGIEnvironmentVariables.hpp"
#include "ProcessCGI.hpp"
#include "FilesToCGI.hpp"

class ChildProcessCGI : public ProcessCGI {
 public:
  ChildProcessCGI(const ArrayChar &cgiPath,
                         const CGIEnvironmentVariables &cgiEnvironmentVariables,
                        FilesToCGI &filesToCGI);
  ~ChildProcessCGI();
  ChildProcessCGI(const ChildProcessCGI &src);
  ChildProcessCGI &operator=(const ChildProcessCGI &src);
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