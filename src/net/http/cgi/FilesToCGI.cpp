#include "FilesToCGI.hpp"

#include <fcntl.h>

#include <fstream>
#include <sstream>

const std::string FilesToCGI::inputFileName = "input";
const std::string FilesToCGI::outputFileName = "output";
const std::string FilesToCGI::stderrFileName = "stderr";

std::string FilesToCGI::defaultDirectoryToSaveTheFiles = "tmp/";

FilesToCGI::FilesToCGI()
    : _logger(NULL),
      _systemCalls(new SystemCalls),
      _inputFileDescriptor(-1),
      _outputFileDescriptor(-1),
      _stderrFileDescriptor(-1) {}

FilesToCGI::FilesToCGI(Log *logger)
    : _logger(logger),
      _systemCalls(new SystemCalls),
      _inputFileDescriptor(-1),
      _outputFileDescriptor(-1),
      _stderrFileDescriptor(-1) {}

FilesToCGI::~FilesToCGI() {
  deleteFiles();
  if (_systemCalls) {
    delete _systemCalls;
  }
}

// deleted, this class must be unique!!!
FilesToCGI::FilesToCGI(const FilesToCGI &src) { *this = src; }

// deleted, this class must be unique!!!
FilesToCGI &FilesToCGI::operator=(const FilesToCGI &src) {
  (void)src;
  return *this;
}

bool FilesToCGI::createFileDescriptors(const HTTPRequest &request) {
  std::string inputFileNameFullPath =
      defaultDirectoryToSaveTheFiles + inputFileName;
  std::string outputFileNameFullPath =
      defaultDirectoryToSaveTheFiles + outputFileName;
  std::string stdErrFileNameFullPath =
      defaultDirectoryToSaveTheFiles + stderrFileName;

  _inputFileDescriptor = openAFile(inputFileNameFullPath);
  if (_inputFileDescriptor == -1) {
    deleteFiles();
    return false;
  }
  _outputFileDescriptor = openAFile(outputFileNameFullPath);
  if (_outputFileDescriptor == -1) {
    deleteFiles();
    return false;
  }
  _stderrFileDescriptor = openAFile(stdErrFileNameFullPath);
  if (_outputFileDescriptor == -1) {
    deleteFiles();
    return false;
  }

  std::ofstream inputFileToFill(inputFileNameFullPath.c_str());
  if (!inputFileToFill.is_open()) {
    _logger->log(
        Log::ERROR, "FilesToCGI", "openFile",
        "Could not open input file to populate it with HTTPRequest body", "");
    deleteFiles();
    return false;
  }
  inputFileToFill << request.getBody();
  return true;
}

// run it in the child process! Before execve.
bool FilesToCGI::prepareFileDescriptorsToChildProcess(int fdIn, int fdOut,
                                                      int fdErr) {
  (void)fdOut;
  error::StatusOr<int> sysCallReturn =
      _systemCalls->dup2(_inputFileDescriptor, fdIn);
  if (!sysCallReturn.ok()) {
    _logger->log(Log::ERROR, "FilesToCGI",
                 "prepareFileDescriptorsToChildProcess",
                 sysCallReturn.status().message(), "fdIn");
    return false;
  }

  sysCallReturn = _systemCalls->dup2(_outputFileDescriptor, fdOut);
  if (!sysCallReturn.ok()) {
    _logger->log(Log::ERROR, "FilesToCGI",
                 "prepareFileDescriptorsToChildProcess",
                 sysCallReturn.status().message(), "fdOut");
    return false;
  }

  sysCallReturn = _systemCalls->dup2(_stderrFileDescriptor, fdErr);
  if (!sysCallReturn.ok()) {
    _logger->log(Log::ERROR, "FilesToCGI",
                 "prepareFileDescriptorsToChildProcess",
                 sysCallReturn.status().message(), "fdErr");
    return false;
  }

  return deleteFiles();
}

int FilesToCGI::openAFile(const std::string fileName) {
  int flags = O_CREAT | O_TRUNC | O_RDWR;
  mode_t mode = S_IRUSR | S_IWUSR;

  if (!_systemCalls) {
    return -1;
  }

  error::StatusOr<int> openFile =
      _systemCalls->open(fileName.c_str(), flags, mode);

  if (openFile.ok()) {
    return openFile.value();
  };

  if (_logger) {
    _logger->log(Log::ERROR, "FilesToCGI", "openFile",
                 openFile.status().message(), fileName);
  }

  return -1;
}

bool FilesToCGI::deleteFiles() {
  bool wereAllFileDescriptorsClosed = true;

  if (_inputFileDescriptor == -1 && _outputFileDescriptor == -1 &&
      _stderrFileDescriptor == -1) {
    return wereAllFileDescriptorsClosed;
  }

  if (!_systemCalls) {
    return false;
  }

  if (closeAFile(_inputFileDescriptor) == false) {
    wereAllFileDescriptorsClosed = false;
  }
  _inputFileDescriptor = -1;

  if (closeAFile(_outputFileDescriptor) == false) {
    wereAllFileDescriptorsClosed = false;
  }
  _outputFileDescriptor = -1;

  if (closeAFile(_stderrFileDescriptor) == false) {
    wereAllFileDescriptorsClosed = false;
  }
  _stderrFileDescriptor = -1;

  return wereAllFileDescriptorsClosed;
}

// return true if the fileDescriptor is invalid or was closed
bool FilesToCGI::closeAFile(int fileDescriptor) {
  if (!_systemCalls) {
    return true;
  }

  if (fileDescriptor == -1) {
    return true;
  }

  error::StatusOr<int> wereTheFileDescriptoClosed =
      _systemCalls->close(fileDescriptor);
  if (wereTheFileDescriptoClosed.ok()) {
    return true;
  }

  if (_logger) {
    _logger->log(Log::ERROR, "FilesToCGI", "closeFile",
                 wereTheFileDescriptoClosed.status().message(), fileDescriptor);
  }

  return false;
}

void FilesToCGI::setSystemCalls(SystemCalls *systemCalls) {
  if (_systemCalls) {
    delete _systemCalls;
  }
  _systemCalls = systemCalls;
}

int FilesToCGI::getInputFileDescriptor() { return _inputFileDescriptor; }

int FilesToCGI::getOutputFileDescriptor() { return _outputFileDescriptor; }

int FilesToCGI::getStderrFileDescriptor() { return _stderrFileDescriptor; }

void FilesToCGI::setInputFileDescriptor(int inputFileDescriptor) {
  _inputFileDescriptor = inputFileDescriptor;
}

void FilesToCGI::setOutputFileDescriptor(int outputFileDescriptor) {
  _outputFileDescriptor = outputFileDescriptor;
}

void FilesToCGI::setStderrFileDescriptor(int stderrFileDescriptor) {
  _stderrFileDescriptor = stderrFileDescriptor;
}

void FilesToCGI::setDefaultDirectoryToSaveTheFiles(
    const std::string &newDirectory) {
  FilesToCGI::defaultDirectoryToSaveTheFiles = newDirectory;
}

std::string FilesToCGI::getDefaultDirectoryToSaveTheFiles() {
  return FilesToCGI::defaultDirectoryToSaveTheFiles;
}

std::ifstream &FilesToCGI::getOutputFile() {
  std::string outputFileNameFullPath =
      defaultDirectoryToSaveTheFiles + outputFileName;
  _outputFile.open(outputFileNameFullPath.c_str());
  return _outputFile;
}

std::ifstream &FilesToCGI::getStderrFile() {
  std::string stderrFileNameFullPath =
      defaultDirectoryToSaveTheFiles + stderrFileName;
  _srtErrFile.open(stderrFileNameFullPath.c_str());
  return _srtErrFile;
}
