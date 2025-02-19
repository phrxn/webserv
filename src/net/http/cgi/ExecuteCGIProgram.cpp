#include "ExecuteCGIProgram.hpp"

#include "../../../error/LogDefault.hpp"
#include "../../../io/File.hpp"
#include "CGIEnvironmentVariables.hpp"
#include "ChildProcessCGI.hpp"
#include "ParentProcessCGI.hpp"

ExecuteCGIProgram::ExecuteCGIProgram()
    : _systemCalls(new SystemCalls), _logger(LogDefault::loggerGlobal) {}

ExecuteCGIProgram::~ExecuteCGIProgram() {
  if (_systemCalls) {
    delete _systemCalls;
  }
}

ExecuteCGIProgram::ExecuteCGIProgram(const ExecuteCGIProgram &src)
    : _systemCalls(new SystemCalls(*src._systemCalls)), _logger(src._logger) {}

ExecuteCGIProgram &ExecuteCGIProgram::operator=(const ExecuteCGIProgram &src) {
  if (this == &src) {
    return *this;
  }
  if (_systemCalls) {
    delete _systemCalls;
  }
  _logger = src._logger;
  return *this;
}

ProcessCGI::ExitStatus ExecuteCGIProgram::execute(
    const std::string &virtualHostRootPath,
    const std::string &physicalPathToResource, HTTPRequest &request,
    FilesToCGI &_filesToCGI) {
  ProcessCGI::ExitStatus _executionResult = ProcessCGI::PARENT_ERROR;

  CGIBinary _cgiBinary =
      CGIBinaryFactory().getCGIBinary(physicalPathToResource);

  if (!cgiBinaryValid(_cgiBinary)) {
    return ProcessCGI::PARENT_ERROR;
  }

  ArrayChar _arrayChar;
  _arrayChar.addString(_cgiBinary.getPathToBinary());
  _arrayChar.addString(_cgiBinary.getPathToScriptToExecute());

  CGIEnvironmentVariables _cgiEnvironmentVariables(physicalPathToResource, virtualHostRootPath, &request);

  error::StatusOr<int> forkReturn = _systemCalls->fork();
  if (!forkReturn.ok()) {
    _logger->log(Log::ERROR, "ExecuteCGIProgram", "execute",
                 forkReturn.status().message(), "");
    return ProcessCGI::PARENT_ERROR;
  }

  pid_t _pid = forkReturn.value();

  if (_pid == -1) {
    return ProcessCGI::PARENT_ERROR;
  }
  if (_pid == 0) {
    ChildProcessCGI _childExecuteProcessCGI(
        _arrayChar, _cgiEnvironmentVariables, _filesToCGI);
    _childExecuteProcessCGI.execute();
  } else {
    ParentProcessCGI _parentExecuteProcessCGI(_pid);
    _executionResult = _parentExecuteProcessCGI.execute();
  }
  return _executionResult;
}

bool ExecuteCGIProgram::cgiBinaryValid(const CGIBinary &cgiBinary) const {

  File _fileCGIBinary(cgiBinary.getPathToBinary());
  if (!_fileCGIBinary.exist()) {
	_logger->log(Log::ERROR, "ExecuteCGIProgram", "cgiBinaryValid", "the cgi binary doesn't exist", cgiBinary.getPathToBinary());
    return false;
  }

  File _fileScriptFile(cgiBinary.getPathToScriptToExecute());
  if (!_fileScriptFile.exist()) {
	_logger->log(Log::ERROR, "ExecuteCGIProgram", "cgiBinaryValid", "the file to cgi doesn't exist", cgiBinary.getPathToScriptToExecute());
    return false;
  }
  return true;
}