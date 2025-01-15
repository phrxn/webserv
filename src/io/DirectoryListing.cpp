#include "DirectoryListing.hpp"

#include <dirent.h>

DirectoryListing::DirectoryListing(const std::string &pathToDir)
    : _pathToDir(pathToDir) {}

DirectoryListing::~DirectoryListing() {}

DirectoryListing::DirectoryListing(const DirectoryListing &src) { *this = src; }

DirectoryListing &DirectoryListing::operator=(const DirectoryListing &src) {
  if (this == &src) return *this;
  _pathToDir = src._pathToDir;
  return *this;
}

std::vector<std::string> DirectoryListing::listFiles() const {
  std::vector<std::string> thingsInsideTheDirectory;

  DIR *directoryToList = opendir(_pathToDir.c_str());
  if (directoryToList == NULL) {
    return thingsInsideTheDirectory;
  }

  struct dirent *entry;
  while ((entry = readdir(directoryToList)) != NULL) {
    thingsInsideTheDirectory.push_back(entry->d_name);
  }

  closedir(directoryToList);

  return thingsInsideTheDirectory;
}