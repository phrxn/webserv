#ifndef IO_FILE_HPP
#define IO_FILE_HPP

#include <unistd.h>

#include <string>
#include <vector>

#include "../error/Log.hpp"
#include "../system/SystemCalls.hpp"
#include "DirectoryListing.hpp"

class DirectoryListing;

class File {
 public:
  File();
  File(const std::string &path);
  File(const std::string &path, Log *logger);
  File(const std::string &path, Log *logger, DirectoryListing *directoryListing);
  ~File();
  File(const File &src);
  File &operator=(const File &src);
  bool operator==(const File &src) const;
  bool operator<(const File &src) const;

  bool isFile() const;

  bool isDirectory() const;

  bool isReadable() const;

  bool isWritable() const;

  bool isExecutable() const;

  const std::string &getPath() const;

  bool exist() const;

  ssize_t size() const;

  std::vector<File> listFiles() const;

  void setSystemCalls(SystemCalls *systemCalls);
  void setLog(Log *log);

 private:
  SystemCalls *_systemCalls;
  std::string _path;
  Log *_logger;
  DirectoryListing *_directoryListing;
};

#endif