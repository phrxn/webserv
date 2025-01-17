#ifndef START_CREATE_MIME_TYPE_MAP_HPP
#define START_CREATE_MIME_TYPE_MAP_HPP

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "../error/StatusOr.hpp"
#include "../system/Errno.hpp"

class CreateMimeTypeMap {
 public:
  CreateMimeTypeMap();
  ~CreateMimeTypeMap();

  error::StatusOr<std::map<std::string, std::string> > loadMimetypeMap(
      const std::string &pathToMimetypeFile) const;
  std::map<std::string, std::string> createAMapOfMimetypeFromAValidLinesMap(
      const std::map<int, std::string> &mapLines) const;
  std::map<int, std::string> readLines(std::istream &inputStream) const;

  std::map<std::string, std::string> createAMapOfMimetypeFromAValidLine(
      const std::string &validLine) const;
  bool lineHasAMimetypeAndAtLeastOneExtesion(const std::string &line) const;
  error::Status areLinesValid(std::map<int, std::string> &lines) const;

  void setErrno(Errno *newErrno);

 private:
  CreateMimeTypeMap(const CreateMimeTypeMap &src);
  CreateMimeTypeMap &operator=(const CreateMimeTypeMap &src);

  Errno *_theErrno;
  std::ifstream _ifstreamMimetypeFile;
};

#endif