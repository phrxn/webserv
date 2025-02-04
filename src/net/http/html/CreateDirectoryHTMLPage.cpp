#include "CreateDirectoryHTMLPage.hpp"

#include <sstream>

CreateDirectoryHTMLPage::CreateDirectoryHTMLPage(
    const std::string& directoryPath, const std::string& urlPathToDir)
    : _directoryPath(directoryPath), _urlPathToDir(urlPathToDir) {}

CreateDirectoryHTMLPage::~CreateDirectoryHTMLPage() {}

CreateDirectoryHTMLPage::CreateDirectoryHTMLPage(
    const CreateDirectoryHTMLPage& src)
    : _directoryPath(src._directoryPath),
      _urlPathToDir(src._urlPathToDir),
      _body(src._body),
      _paths(src._paths) {}

CreateDirectoryHTMLPage& CreateDirectoryHTMLPage::operator=(
    const CreateDirectoryHTMLPage& src) {
  if (this == &src) {
    return *this;
  }
  _directoryPath = src._directoryPath;
  _urlPathToDir = src._urlPathToDir;
  _body = src._body;
  _paths = src._paths;
  return *this;
}

CreateDirectoryHTMLPage& CreateDirectoryHTMLPage::operator<<(
    const ItemDirectoryHTMLDocument& item) {
  std::stringstream ss;
  ss << createAnchorToPath(item) << " ";
  ss << formatData(item) << " ";
  ss << item.getSizeInBytes() << "\n";

  _paths.push_back(ss.str());

  return *this;
}

std::string CreateDirectoryHTMLPage::createAnchorToPath(
    const ItemDirectoryHTMLDocument& item) const {
  std::stringstream ss;
  ss << "<a href=\"" << item.getPath() << "\">";
  std::string formattedPath = formatPath(item);
  ss << formattedPath << "</a>";
  if (formattedPath.size() < 50) {
    std::string blankSpaces;
    blankSpaces.append(50 - formattedPath.size(), ' ');
    ss << blankSpaces;
  }
  return ss.str();
}

std::string CreateDirectoryHTMLPage::formatPath(
    const ItemDirectoryHTMLDocument& item) const {
  std::string pathFormatted = item.getPath();

  if (pathFormatted.size() < 51) {
    return pathFormatted;
  }

  if (item.isDirectory() && pathFormatted.size() == 51) {
    pathFormatted.resize(50);
    return pathFormatted;
  }

  pathFormatted.resize(47);
  pathFormatted.append("..&gt;");

  return pathFormatted;
}

std::string CreateDirectoryHTMLPage::formatData(
    const ItemDirectoryHTMLDocument& item) const {
  std::string dataFormatted = item.getModificationTime();

  return dataFormatted.append(35 - dataFormatted.size(), ' ');
}

std::string CreateDirectoryHTMLPage::str() {
  std::stringstream ss;

  ss << "<html>\n"
     << "<head><title>Index of " << _urlPathToDir << "</title></head>\n"
     << "<body>\n"
     << "<h1>Index of " << _urlPathToDir << "</h1>\n"
     << "<hr>\n"
     << "<pre>\n"
     << "<a href=\"../\">../</a>\n";

  std::list<std::string>::const_iterator it = _paths.begin();
  std::list<std::string>::const_iterator end = _paths.end();
  for (; it != end; ++it) {
    ss << *it;
  }

  ss << "</pre>\n"
     << "<hr>\n"
     << "</body>\n"
     << "</html>\n";

  return ss.str();
}

std::string CreateDirectoryHTMLPage::getBody() const { return _body; }

void CreateDirectoryHTMLPage::setBody(const std::string& body) { _body = body; }