#include "MimeType.hpp"

std::map<std::string, std::string> MimeType::_mimeTypeMap;

MimeType::MimeType() {}

MimeType::~MimeType() {}

MimeType::MimeType(const MimeType &src) { *this = src; }

MimeType &MimeType::operator=(const MimeType &src) {
  (void)src;
  return *this;
}

// this function extract the part after dot from a string.
// If
std::string MimeType::getExtensionFromPath(const std::string &path) const {
  std::string::size_type dotPosition = path.find_last_of(".");
  if (dotPosition == std::string::npos) {
    return path;
  }
  if (dotPosition == path.size() - 1) {
    return "";
  }
  return path.substr(dotPosition + 1);
}

std::string MimeType::getMimeTypeByFileExtesion(
    const std::string &fileExtension) {
  std::string theFileExtesion = getExtensionFromPath(fileExtension);

  std::map<std::string, std::string>::const_iterator it =
      _mimeTypeMap.find(theFileExtesion);

  if (it != _mimeTypeMap.end()) {
    return it->second;
  }
  return "application/octet-stream";
}

void MimeType::setMimetypeMap(
    const std::map<std::string, std::string> &mimeTypeMap) {
  _mimeTypeMap = mimeTypeMap;
}