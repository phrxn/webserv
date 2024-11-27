#include "FileDescriptor.hpp"

FileDescriptor::FileDescriptor(int fd)
    : _fd(fd),
      _systemCalls(new SystemCalls),
      _isReadyToRead(false),
      _isReadyToWrite(false) {}

// protected (this class or its heirs MUST BE UNIQUE!)
FileDescriptor::FileDescriptor(const FileDescriptor &src)
    : _systemCalls(src._systemCalls) {
  (void)src;
}

FileDescriptor::~FileDescriptor() {
  if (_systemCalls) {
    _systemCalls->close(_fd);
    delete _systemCalls;
  }
}

// deleted (this class or its heirs MUST BE UNIQUE!)
FileDescriptor &FileDescriptor::operator=(const FileDescriptor &src) {
  (void)src;
  return *this;
}

bool FileDescriptor::isReadyToRead() const { return _isReadyToRead; }
bool FileDescriptor::isReadyToWrite() const { return _isReadyToWrite; }

void FileDescriptor::setSystemCalls(SystemCalls *systemCalls) {
  if (_systemCalls) delete _systemCalls;
  _systemCalls = systemCalls;
}

void FileDescriptor::setReadyToRead(bool isReadyToRead) {
  _isReadyToRead = isReadyToRead;
}
void FileDescriptor::setReadyToWrite(bool isReadyToWrite) {
  _isReadyToWrite = isReadyToWrite;
}

int FileDescriptor::getFileDescriptor() const { return _fd; }