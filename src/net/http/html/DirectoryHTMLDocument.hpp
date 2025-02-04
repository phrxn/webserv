#ifndef NET_HTTP_HTML_DIRECTORY_HTML_DOCUMENT_HPP
#define NET_HTTP_HTML_DIRECTORY_HTML_DOCUMENT_HPP

#include <string>

#include "../../../io/File.hpp"
#include "HTMLDocument.hpp"
#include "ItemDirectoryHTMLDocument.hpp"

class DirectoryHTMLDocument : public HTMLDocument {
 public:
  DirectoryHTMLDocument(const std::string &pathToDirectory, const std::string& urlPathToDir);
  DirectoryHTMLDocument(File *directoryToCreateList, const std::string& urlPathToDir);
  ~DirectoryHTMLDocument();
  DirectoryHTMLDocument(const DirectoryHTMLDocument &src);
  DirectoryHTMLDocument &operator=(const DirectoryHTMLDocument &src);

  std::string getData() const;
  std::size_t getSize() const;
  std::string getMimeType() const;
  std::string getLastModified() const;
  HTTPStatus::Status getStatus() const;
  virtual HTMLDocument* clone() const;

  void createDirectoryListFileHTML(File *directoryToCreateList);

  void removeDotAndDotDotDirectoriesFromDirectoryList(
      std::vector<File> &listFilesInsideDirectory);

  void sortDirectoryFiles(std::vector<File> &listToSort);
  void sortDirectoryFiles(std::vector<File *> &listToSort);

std::vector<ItemDirectoryHTMLDocument> createItemDirectoryHTMLDocumentList(
    std::vector<File> &listFilesInsideDirectory);

 private:
  void freeThings();

  HTTPStatus::Status _status;
  File *_directory;
  std::string _data;
  std::string _urlPathToDir;

};

bool compareFiles(File *a, File *b);

#endif