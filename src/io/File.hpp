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
  virtual ~File();
  File(const File &src);
  File &operator=(const File &src);
  bool operator==(const File &src) const;
  bool operator<(const File &src) const;

  bool isFile() const;

  virtual bool isDirectory() const;

  time_t getModificationTime() const;

  std::string getPath() const;

  void setPath(const std::string &path);

  bool exist() const;

  ssize_t size() const;

  std::vector<File> listFiles() const;

  void setSystemCalls(SystemCalls *systemCalls);

  void setLog(Log *log);
 protected:
  std::string _path;

 private:
  SystemCalls *_systemCalls;
  Log *_logger;
  DirectoryListing *_directoryListing;
};

#endif