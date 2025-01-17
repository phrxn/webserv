#include "CreateMimeTypeMap.hpp"

#include <sstream>

CreateMimeTypeMap::CreateMimeTypeMap() : _theErrno(new Errno) {}

CreateMimeTypeMap::~CreateMimeTypeMap() {
  if (_theErrno) {
    delete _theErrno;
  }
}

//deleted
CreateMimeTypeMap::CreateMimeTypeMap(const CreateMimeTypeMap &src){
	(void)src;
}

//deleted
CreateMimeTypeMap &CreateMimeTypeMap::operator=(const CreateMimeTypeMap &src) {
	(void)src;
	return *this;
}

error::StatusOr<std::map<std::string, std::string> >
CreateMimeTypeMap::loadMimetypeMap(
    const std::string &pathToMimetypeFile) const {
  std::ifstream mimeTypeFile(pathToMimetypeFile.c_str());
  if (!mimeTypeFile.is_open()) {
    std::stringstream ssErrorMessage;
    ssErrorMessage << "Could not open mimetype file: " << pathToMimetypeFile
                   << ": " << _theErrno->getErrorMessage();
    return error::Status(error::Status::FileOpen, ssErrorMessage.str());
  }

  std::map<int, std::string> allLines = readLines(mimeTypeFile);

  error::Status areAllLinesValid = areLinesValid(allLines);
  if (!areAllLinesValid.ok()) {
    return areAllLinesValid;
  }

  return createAMapOfMimetypeFromAValidLinesMap(allLines);
}

std::map<std::string, std::string>
CreateMimeTypeMap::createAMapOfMimetypeFromAValidLinesMap(
    const std::map<int, std::string> &mapLines) const {
  std::map<std::string, std::string> mapWithMimeTypes;

  std::map<int, std::string>::const_iterator it = mapLines.begin();
  std::map<int, std::string>::const_iterator end = mapLines.end();

  for (; it != end; ++it) {
    std::map<std::string, std::string> tmpMap =
        createAMapOfMimetypeFromAValidLine(it->second);
    mapWithMimeTypes.insert(tmpMap.begin(), tmpMap.end());
  }

  return mapWithMimeTypes;
}

std::map<int, std::string> CreateMimeTypeMap::readLines(
    std::istream &inputStream) const {
  int countLines = 1;
  std::string tmpLine;
  std::map<int, std::string> mapLines;

  while (std::getline(inputStream, tmpLine)) {
    if (!tmpLine.empty()) {
      mapLines.insert(std::make_pair(countLines, tmpLine));
    }
    countLines++;
  }

  return mapLines;
}

// the line must be valid (the line must have at least 2 words)
std::map<std::string, std::string>
CreateMimeTypeMap::createAMapOfMimetypeFromAValidLine(
    const std::string &validLine) const {
  std::map<std::string, std::string> mapToReturn;
  std::pair<std::string, std::string> tmpPair;

  std::stringstream ss(validLine);

  ss >> tmpPair.second;

  while (true) {
    ss >> tmpPair.first;
    if (ss.fail()) {
      break;
    }
    mapToReturn.insert(tmpPair);
  }
  return mapToReturn;
}

bool CreateMimeTypeMap::lineHasAMimetypeAndAtLeastOneExtesion(
    const std::string &line) const {
  std::stringstream ss(line);

  std::string someText;
  ss >> someText >> someText;

  if (ss.fail()) {
    return false;
  }

  return true;
}

error::Status CreateMimeTypeMap::areLinesValid(
    std::map<int, std::string> &lines) const {
  if (lines.size() == 0) {
    return error::Status(error::Status::FileOpen, "The mimetype file is empty");
  }

  std::map<int, std::string>::const_iterator it = lines.begin();
  std::map<int, std::string>::const_iterator end = lines.end();

  for (; it != end; ++it) {
    if (!lineHasAMimetypeAndAtLeastOneExtesion(it->second)) {
      std::stringstream ssMessageError;
      ssMessageError
          << "The line: " << it->first
          << " is not valid, if the line isn't a line break, it must "
             "have at least one mime type and one extesion";
      return error::Status(error::Status::FileOpen, ssMessageError.str());
    }
  }
  return error::Status::OK;
}

void CreateMimeTypeMap::setErrno(Errno *newErrno) {
  if (_theErrno) {
    delete _theErrno;
  }
  _theErrno = newErrno;
}