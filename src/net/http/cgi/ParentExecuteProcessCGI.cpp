#include "ParentExecuteProcessCGI.hpp"

#include <sys/wait.h>

#include "../../../config/ProgramConfiguration.hpp"

ParentExecuteProcessCGI::ParentExecuteProcessCGI(pid_t childPid)
    : _systemCalls(new SystemCalls),
      _logger(LogDefault::loggerGlobal),
      _childPid(childPid),
      _timeToWaitThChildProcessInSeconds(
          ProgramConfiguration::getInstance()
              .getTimeToWaitTheChildCGIProcessInSeconds()) {}

ParentExecuteProcessCGI::ParentExecuteProcessCGI(
    pid_t childPid, int timeToWaitThChildProcessInSeconds)
    : _systemCalls(new SystemCalls),
	  _logger(LogDefault::loggerGlobal),
      _childPid(childPid),
      _timeToWaitThChildProcessInSeconds(timeToWaitThChildProcessInSeconds) {}

ParentExecuteProcessCGI::~ParentExecuteProcessCGI() {
  if (_systemCalls) {
    delete _systemCalls;
  }
}

ParentExecuteProcessCGI::ExitStatus ParentExecuteProcessCGI::execute() {
  std::time_t startTime = _time.getCurrentTime();

  pid_t waitReturn = 0;
  int status = -1;
  bool isChildKilled = false;

  while (true) {
    if (_time.isTimeOut(startTime, _timeToWaitThChildProcessInSeconds) && !isChildKilled) {
      error::StatusOr<int> ret = _systemCalls->kill(_childPid, SIGKILL);
      if (!ret.ok()) {
        _logger->log(Log::ERROR, "ParentExecuteProcessCGI", "execute", ret.status().message(), _childPid);
        return ExecuteProcessCGI::PARENT_ERROR;
      }
      isChildKilled = true;
	  _logger->log(Log::ERROR, "ParentExecuteProcessCGI", "execute", "the CGI child process took too long to execute", _childPid);
    }

    error::StatusOr<pid_t> ret = _systemCalls->waitpid(_childPid, &status, WNOHANG);
    if (!ret.ok()) {
      _logger->log(Log::ERROR, "ParentExecuteProcessCGI", "execute", ret.status().message(), _childPid);
      return ExecuteProcessCGI::PARENT_ERROR;
    }

	// if the value is 0, the child is still running, let's wait a little bit more :)
    waitReturn = ret.value();
    if (waitReturn == 0) {
      continue;
    }

    if (WIFEXITED(status)) {
      return WEXITSTATUS(status) == 0
                 ? ExecuteProcessCGI::CHILD_EXIT_OK
                 : ExecuteProcessCGI::CHILD_EXIT_WITH_ERROR;
    }
    if (WIFSIGNALED(status)) {
      return ExecuteProcessCGI::CHILD_FINISHED_BY_SIGNAL;
    }
  }
}

void ParentExecuteProcessCGI::setSystemCalls(SystemCalls *systemCalls) {
  if (_systemCalls) {
    delete _systemCalls;
  }
  _systemCalls = systemCalls;
}

void ParentExecuteProcessCGI::setLogger(Log *logger) {
  _logger = logger;
}