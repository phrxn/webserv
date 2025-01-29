#include "GetMimeType.hpp"

std::map<std::string, std::string> GetMimeType::_mimeTypeMap;

GetMimeType::GetMimeType() {}

GetMimeType::~GetMimeType() {}

GetMimeType::GetMimeType(const GetMimeType &src) { *this = src; }

GetMimeType &GetMimeType::operator=(const GetMimeType &src) {
  (void)src;
  return *this;
}

// this function extract the part after dot from a string.
// If
std::string GetMimeType::getExtensionFromPath(const std::string &path) const {
  std::string::size_type dotPosition = path.find_last_of(".");
  if (dotPosition == std::string::npos) {
    return path;
  }
  if (dotPosition == path.size() - 1) {
    return "";
  }
  return path.substr(dotPosition + 1);
}

std::string GetMimeType::getMimeTypeByFileExtesion(
    const std::string &fileExtension) {
  std::string theFileExtesion = getExtensionFromPath(fileExtension);

  std::map<std::string, std::string>::const_iterator it =
      _mimeTypeMap.find(theFileExtesion);

  if (it != _mimeTypeMap.end()) {
    return it->second;
  }
  return "application/octet-stream";
}

void GetMimeType::setMimetypeMap(
    const std::map<std::string, std::string> &mimeTypeMap) {
  _mimeTypeMap = mimeTypeMap;
}