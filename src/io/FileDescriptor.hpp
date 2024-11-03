#ifndef IO_FILE_DESCRIPTOR_HPP
#define IO_FILE_DESCRIPTOR_HPP

#include <vector>

#include "../net/FileDescriptorVisitor.hpp"
#include "../system/SystemCalls.hpp"

class FileDescriptor {
 public:
  FileDescriptor(int fd);

  virtual ~FileDescriptor();

  int getFileDescriptor() const;

  bool isReadyToRead() const;
  bool isReadyToWrite() const;

  void setSystemCalls(SystemCalls *systemCalls);

  virtual void setReadyToRead(bool isReadyToRead);
  virtual void setReadyToWrite(bool isReadyToWrite);

  virtual void acceptVisit(FileDescriptorVisitor *fdv) = 0;

 protected:
  FileDescriptor(const FileDescriptor &src);

  int _fd;
  const SystemCalls *_systemCalls;

 private:
  FileDescriptor &operator=(const FileDescriptor &src);

  bool _isReadyToRead;
  bool _isReadyToWrite;
};

#endif
