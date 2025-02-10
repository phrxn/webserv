#ifndef NET_HTTP_CGI_PARENT_PROCESS_CGI_HPP
#define NET_HTTP_CGI_PARENT_PROCESS_CGI_HPP

#include "../../../system/SystemCalls.hpp"
#include "../../../time/Time.hpp"
#include "../../../error/LogDefault.hpp"
#include "ProcessCGI.hpp"

class ParentProcessCGI : public ProcessCGI {
 public:
  ParentProcessCGI(pid_t childPid);
  ParentProcessCGI(pid_t childPid, int timeToWaitThChildProcessInSeconds);
  virtual ~ParentProcessCGI();
  ExitStatus execute();
  void setSystemCalls(SystemCalls *systemCalls);
  void setLogger(Log *logger);

 private:
  SystemCalls *_systemCalls;
  Log *_logger;
  pid_t _childPid;
  int _timeToWaitThChildProcessInSeconds;
  Time _time;
};

#endif