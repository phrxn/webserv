#include "ParentProcessCGI.hpp"

#include <sys/wait.h>

#include "../../../config/ProgramConfiguration.hpp"

ParentProcessCGI::ParentProcessCGI(pid_t childPid)
    : _systemCalls(new SystemCalls),
      _logger(LogDefault::loggerGlobal),
      _childPid(childPid),
      _timeToWaitThChildProcessInSeconds(
          ProgramConfiguration::getInstance()
              .getTimeToWaitTheChildCGIProcessInSeconds()) {}

ParentProcessCGI::ParentProcessCGI(
    pid_t childPid, int timeToWaitThChildProcessInSeconds)
    : _systemCalls(new SystemCalls),
	  _logger(LogDefault::loggerGlobal),
      _childPid(childPid),
      _timeToWaitThChildProcessInSeconds(timeToWaitThChildProcessInSeconds) {}

ParentProcessCGI::~ParentProcessCGI() {
  if (_systemCalls) {
    delete _systemCalls;
  }
}

ParentProcessCGI::ExitStatus ParentProcessCGI::execute() {
  std::time_t startTime = _time.getCurrentTime();

  pid_t waitReturn = 0;
  int status = -1;
  bool isChildKilled = false;

  while (true) {
    if (_time.isTimeOut(startTime, _timeToWaitThChildProcessInSeconds) && !isChildKilled) {
      error::StatusOr<int> ret = _systemCalls->kill(_childPid, SIGKILL);
      if (!ret.ok()) {
        _logger->log(Log::ERROR, "ParentProcessCGI", "execute", ret.status().message(), _childPid);
        return ProcessCGI::PARENT_ERROR;
      }
      isChildKilled = true;
	  _logger->log(Log::ERROR, "ParentProcessCGI", "execute", "the CGI child process took too long to execute", _childPid);
    }

    error::StatusOr<pid_t> ret = _systemCalls->waitpid(_childPid, &status, WNOHANG);
    if (!ret.ok()) {
      _logger->log(Log::ERROR, "ParentProcessCGI", "execute", ret.status().message(), _childPid);
      return ProcessCGI::PARENT_ERROR;
    }

	// if the value is 0, the child is still running, let's wait a little bit more :)
    waitReturn = ret.value();
    if (waitReturn == 0) {
      continue;
    }

    if (WIFEXITED(status)) {
      return WEXITSTATUS(status) == 0
                 ? ProcessCGI::CHILD_EXIT_OK
                 : ProcessCGI::CHILD_EXIT_WITH_ERROR;
    }
    if (WIFSIGNALED(status)) {
      return ProcessCGI::CHILD_FINISHED_BY_SIGNAL;
    }
  }
}

void ParentProcessCGI::setSystemCalls(SystemCalls *systemCalls) {
  if (_systemCalls) {
    delete _systemCalls;
  }
  _systemCalls = systemCalls;
}

void ParentProcessCGI::setLogger(Log *logger) {
  _logger = logger;
}