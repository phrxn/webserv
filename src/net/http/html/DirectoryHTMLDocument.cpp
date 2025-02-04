#include "DirectoryHTMLDocument.hpp"

#include <algorithm>

#include "CreateDirectoryHTMLPage.hpp"

DirectoryHTMLDocument::DirectoryHTMLDocument(const std::string &pathToDirectory,
                                             const std::string &urlPathToDir)
    : _directory(new File(pathToDirectory)), _urlPathToDir(urlPathToDir) {
  createDirectoryListFileHTML(_directory);
}

DirectoryHTMLDocument::DirectoryHTMLDocument(File *directoryToCreateList,
                                             const std::string &urlPathToDir)
    : _directory(directoryToCreateList), _urlPathToDir(urlPathToDir) {}

DirectoryHTMLDocument::~DirectoryHTMLDocument() { freeThings(); }

DirectoryHTMLDocument::DirectoryHTMLDocument(const DirectoryHTMLDocument &src)
    : _status(src._status),
      _directory(new File(*src._directory)),
      _urlPathToDir(src._urlPathToDir) {}

DirectoryHTMLDocument &DirectoryHTMLDocument::operator=(
    const DirectoryHTMLDocument &src) {
  if (this == &src) return *this;
  freeThings();
  _status = src._status;
  _directory = new File(*src._directory);
  _urlPathToDir = src._urlPathToDir;
  return *this;
}

std::string DirectoryHTMLDocument::getData() const { return _data; }

std::size_t DirectoryHTMLDocument::DirectoryHTMLDocument::getSize() const {
  return _data.size();
}

std::string DirectoryHTMLDocument::getMimeType() const { return "text/html"; }

std::string DirectoryHTMLDocument::getLastModified() const { return ""; }

HTTPStatus::Status DirectoryHTMLDocument::getStatus() const { return _status; }

HTMLDocument *DirectoryHTMLDocument::clone() const {
  return new DirectoryHTMLDocument(*this);
}

void DirectoryHTMLDocument::createDirectoryListFileHTML(
    File *directoryToCreateList) {
  if (!directoryToCreateList->isDirectory()) {
    _status = HTTPStatus::NOT_FOUND;
    return;
  }

  std::vector<File> filesInsideOfDirectory = directoryToCreateList->listFiles();

  removeDotAndDotDotDirectoriesFromDirectoryList(filesInsideOfDirectory);

  // add fullpath
  std::vector<File>::iterator it1 = filesInsideOfDirectory.begin();
  std::vector<File>::iterator end1 = filesInsideOfDirectory.end();

  for (; it1 != end1; ++it1) {
    std::string fullPath = _directory->getPath() + it1->getPath();
    it1->setPath(fullPath);
  }

  sortDirectoryFiles(filesInsideOfDirectory);

  std::vector<ItemDirectoryHTMLDocument> listAllDirectoryItems =
      createItemDirectoryHTMLDocumentList(filesInsideOfDirectory);

  CreateDirectoryHTMLPage createDirectory(_directory->getPath(), _urlPathToDir);

  std::vector<ItemDirectoryHTMLDocument>::const_iterator it =
      listAllDirectoryItems.begin();
  std::vector<ItemDirectoryHTMLDocument>::const_iterator end =
      listAllDirectoryItems.end();

  for (; it != end; ++it) {
    createDirectory << *it;
  }
  _data = createDirectory.str();
  _status = HTTPStatus::OK;
}

void DirectoryHTMLDocument::sortDirectoryFiles(std::vector<File> &listToSort) {
  std::sort(listToSort.begin(), listToSort.end());
}

void DirectoryHTMLDocument::sortDirectoryFiles(
    std::vector<File *> &listToSort) {
  std::sort(listToSort.begin(), listToSort.end(), compareFiles);
}

bool compareFiles(File *a, File *b) { return *a < *b; }

void DirectoryHTMLDocument::removeDotAndDotDotDirectoriesFromDirectoryList(
    std::vector<File> &listFilesInsideDirectory) {
  std::vector<File>::iterator it = listFilesInsideDirectory.begin();

  while (it != listFilesInsideDirectory.end()) {
    if (it->getPath() == "." || it->getPath() == "..") {
      listFilesInsideDirectory.erase(it);
      continue;
    }
    ++it;
  }
}

std::vector<ItemDirectoryHTMLDocument>
DirectoryHTMLDocument::createItemDirectoryHTMLDocumentList(
    std::vector<File> &listFilesInsideDirectory) {
  std::vector<File>::iterator it = listFilesInsideDirectory.begin();
  std::vector<File>::iterator end = listFilesInsideDirectory.end();

  std::vector<ItemDirectoryHTMLDocument> itemList;

  for (; it != end; ++it) {
    itemList.push_back(ItemDirectoryHTMLDocument(*it, _directory->getPath()));
  }
  return itemList;
}

void DirectoryHTMLDocument::freeThings() {
  if (_directory) {
    delete _directory;
  }
}
