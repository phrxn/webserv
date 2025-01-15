#ifndef IO_DIRECTORY_LISTING_HPP
#define IO_DIRECTORY_LISTING_HPP

#include <string>
#include <vector>

class DirectoryListing {
 public:
  DirectoryListing(const std::string &pathToDir);
  virtual ~DirectoryListing();
  DirectoryListing(const DirectoryListing &src);
  DirectoryListing &operator=(const DirectoryListing &src);

  virtual std::vector<std::string> listFiles() const;

 private:
  std::string _pathToDir;
};

#endif