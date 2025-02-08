#include "ChildExecuteProcessCGI.hpp"

#include <stdexcept>

#include "../../../error/LogDefault.hpp"

ChildExecuteProcessCGI::ChildExecuteProcessCGI(
    const ArrayChar &argv,
    const CGIEnvironmentVariables &cgiEnvironmentVariables,
    FilesToCGI &filesToCGI)
    : _argv(argv),
      _cgiEnvironmentVariables(cgiEnvironmentVariables),
      _filesToCGI(filesToCGI),
      _systemCalls(new SystemCalls),
      _logger(LogDefault::loggerGlobal) {}

ChildExecuteProcessCGI::~ChildExecuteProcessCGI() {}

ChildExecuteProcessCGI::ChildExecuteProcessCGI(
    const ChildExecuteProcessCGI &src)
    : _argv(src._argv),
      _cgiEnvironmentVariables(src._cgiEnvironmentVariables),
      _filesToCGI(src._filesToCGI),
      _systemCalls(new SystemCalls(*src._systemCalls)),
      _logger(src._logger) {}

ChildExecuteProcessCGI &ChildExecuteProcessCGI::operator=(
    const ChildExecuteProcessCGI &src) {
  if (this == &src) return *this;
  if (_systemCalls) {
    delete _systemCalls;
  }
  _argv = src._argv;
  _cgiEnvironmentVariables = src._cgiEnvironmentVariables;
  _systemCalls = new SystemCalls(*src._systemCalls);
  _logger = src._logger;
  return *this;
}

ChildExecuteProcessCGI::ExitStatus ChildExecuteProcessCGI::execute() {
  char **argv = _argv.getPointerToArray();

  _filesToCGI.prepareFileDescriptorsToChildProcess(0, 1, 2);

  _systemCalls->execve(argv[0], argv, _cgiEnvironmentVariables.createEnvironmentVariables());

  throw std::runtime_error("execve");
}

void ChildExecuteProcessCGI::setSystemCalls(SystemCalls *systemCalls) {
  if (_systemCalls) {
    delete _systemCalls;
  }
  _systemCalls = systemCalls;
}

void ChildExecuteProcessCGI::setLogger(Log *logger) { _logger = logger; }