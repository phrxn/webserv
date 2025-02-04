#include "File.hpp"

#include <sys/stat.h>

File::File()
    : _path("/"),
  	  _systemCalls(new SystemCalls),
      _logger(NULL),
      _directoryListing(new DirectoryListing(_path)) {}

File::File(const std::string &path)
    : _path(path),
  	  _systemCalls(new SystemCalls),
      _logger(NULL),
      _directoryListing(new DirectoryListing(_path)) {}

File::File(const std::string &path, Log *logger)
    : _path(path),
  	  _systemCalls(new SystemCalls),
      _logger(logger),
      _directoryListing(new DirectoryListing(_path)) {}

File::File(const std::string &path, Log *logger,
           DirectoryListing *directoryListing)
    : _path(path),
  	  _systemCalls(new SystemCalls),
      _logger(logger),
      _directoryListing(directoryListing) {}

File::~File() {
  if (_systemCalls) {
    delete _systemCalls;
  }
  if (_directoryListing) {
    delete _directoryListing;
  }
}

File::File(const File &src)
    : _path(src._path),
	  _systemCalls(new SystemCalls(*src._systemCalls)),
      _logger(src._logger),
      _directoryListing(new DirectoryListing(*src._directoryListing)) {}

File &File::operator=(const File &src) {
  if (this == &src) {
    return *this;
  }
  if (_systemCalls) {
    delete _systemCalls;
  }
  _systemCalls = new SystemCalls(*src._systemCalls);
  if (_directoryListing) {
    delete _directoryListing;
  }
  _directoryListing = new DirectoryListing(*src._directoryListing);
  _logger = src._logger;
  _path = src._path;
  return *this;
}

bool File::operator==(const File &src) const {
  if (this == &src) return true;
  return (_path == src._path);
}

bool File::operator<(const File &src) const {
  if (!isDirectory() && src.isDirectory()){
	return false;
  }
  if (isDirectory() && !src.isDirectory()) {
    return true;
  }
  return _path < src._path;
}

bool File::isFile() const {
  struct stat file_information;

  error::StatusOr<int> statWasFilledIn =
      _systemCalls->stat(_path.c_str(), &file_information);

  if (!statWasFilledIn.ok() || !S_ISREG(file_information.st_mode)) {
    return false;
  }

  return true;
}

bool File::isDirectory() const {
  struct stat file_information;

  error::StatusOr<int> statWasFilledIn =
      _systemCalls->stat(_path.c_str(), &file_information);

  if (!statWasFilledIn.ok() || !S_ISDIR(file_information.st_mode)) {
    return false;
  }

  return true;
}

time_t File::getModificationTime() const {
  struct stat file_information;

  error::StatusOr<int> statWasFilledIn =
      _systemCalls->stat(_path.c_str(), &file_information);

  if (!statWasFilledIn.ok()) {
    return 0;
  }
  return file_information.st_mtim.tv_sec;
}

std::string File::getPath() const { return _path; }

bool File::exist() const {
  error::StatusOr<int> isReadable = _systemCalls->access(_path.c_str(), F_OK);
  if (isReadable.ok()) {
    return true;
  }
  return false;
}

void File::setPath(const std::string &path){
	_path = path;
}

std::vector<File> File::listFiles() const {
  std::vector<File> fileInsideDirectory;

  std::vector<std::string> files = _directoryListing->listFiles();

  std::vector<std::string>::const_iterator it = files.begin();
  std::vector<std::string>::const_iterator end = files.end();

  for (; it != end; ++it) {
    fileInsideDirectory.push_back(File(*it));
  }
  return fileInsideDirectory;
}

ssize_t File::size() const {
  struct stat file_information;

  error::StatusOr<int> statWasFilledIn =
      _systemCalls->stat(_path.c_str(), &file_information);

  if (statWasFilledIn.ok()) {
    return file_information.st_size;
  }

  if (_logger) {
    _logger->log(Log::ERROR, "File", "size", "get file size",
                 statWasFilledIn.status().message());
  }

  return -1;
}

void File::setSystemCalls(SystemCalls *systemCalls) {
  if (_systemCalls) {
    delete _systemCalls;
  }
  _systemCalls = systemCalls;
}

void File::setLog(Log *logger) {
  if (_logger) {
    delete _logger;
  }
  _logger = logger;
}