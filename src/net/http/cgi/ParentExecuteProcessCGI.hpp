#ifndef NET_HTTP_CGI_PARENT_EXECUTE_PROCESS_CGI_HPP
#define NET_HTTP_CGI_PARENT_EXECUTE_PROCESS_CGI_HPP

#include "../../../system/SystemCalls.hpp"
#include "../../../time/Time.hpp"
#include "../../../error/LogDefault.hpp"
#include "ExecuteProcessCGI.hpp"

class ParentExecuteProcessCGI : public ExecuteProcessCGI {
 public:
  ParentExecuteProcessCGI(pid_t childPid);
  ParentExecuteProcessCGI(pid_t childPid, int timeToWaitThChildProcessInSeconds);
  virtual ~ParentExecuteProcessCGI();
  ExitStatus execute() const;
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