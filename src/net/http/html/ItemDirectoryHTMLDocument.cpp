#include "ItemDirectoryHTMLDocument.hpp"

#include <sstream>

ItemDirectoryHTMLDocument::ItemDirectoryHTMLDocument(const File &file, const std::string &dirParent) : _dirParent(dirParent){
  init(file.getPathFullEncoded(), file.getModificationTime(), file.size(),
       file.isDirectory());
}

ItemDirectoryHTMLDocument::ItemDirectoryHTMLDocument(const std::string &path,
                                                     time_t modificationTime,
                                                     ssize_t sizeInBytes,
                                                     bool isDirectory) {
  init(path, modificationTime, sizeInBytes, isDirectory);
}

ItemDirectoryHTMLDocument::~ItemDirectoryHTMLDocument() {}

ItemDirectoryHTMLDocument::ItemDirectoryHTMLDocument(
    const ItemDirectoryHTMLDocument &src)  {
  *this = src;
}

ItemDirectoryHTMLDocument &ItemDirectoryHTMLDocument::operator=(
    const ItemDirectoryHTMLDocument &src) {
  if (this == &src) return *this;
  _dirParent = src._dirParent;
  _path = src._path;
  _modificationTime = src._modificationTime;
  _sizeInBytes = src._sizeInBytes;
  _isDirectory = src._isDirectory;
  _time = src._time;
  return *this;
}

bool ItemDirectoryHTMLDocument::operator==(
    const ItemDirectoryHTMLDocument &src) {
  return _path == src._path;
}

bool ItemDirectoryHTMLDocument::operator<(
    const ItemDirectoryHTMLDocument &src) {
  if (!_isDirectory && src._isDirectory) {
    return false;
  }
  if (_isDirectory && !src._isDirectory) {
    return true;
  }
  return _path < src._path;
}


std::string ItemDirectoryHTMLDocument::getPathFullEncoded() const {

  std::string _pathFile = _path.substr(_dirParent.size());

  //if the path is a directory and does not end with a slash, add it
  if (_isDirectory && (!_pathFile.empty() && _pathFile[_pathFile.length() - 1] != '/')) {
    return (_pathFile + "/");
  }
  return _pathFile;
}

std::string ItemDirectoryHTMLDocument::getModificationTime() const {
  return _time.convertTimeToItemDirectoryHTML(_modificationTime);
}

std::string ItemDirectoryHTMLDocument::getSizeInBytes() const {
  if (_isDirectory) {
    return "-";
  }
  std::stringstream ss;
  ss << _sizeInBytes;
  return ss.str();
}

bool ItemDirectoryHTMLDocument::isDirectory() const { return _isDirectory; }

void ItemDirectoryHTMLDocument::init(const std::string &path,
                                     time_t modificationTime,
                                     ssize_t sizeInBytes, bool isDirectory) {
  _path = path;
  _modificationTime = modificationTime;
  _sizeInBytes = sizeInBytes;
  _isDirectory = isDirectory;
}