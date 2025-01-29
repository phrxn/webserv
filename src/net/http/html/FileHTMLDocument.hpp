#ifndef NET_HTTP_HTML_FILE_HTML_DOCUMENT_HPP
#define NET_HTTP_HTML_FILE_HTML_DOCUMENT_HPP

#include <fstream>

#include "../../../io/File.hpp"
#include "../../../time/Time.hpp"
#include "../GetMimeType.hpp"
#include "HTMLDocument.hpp"

class FileHTMLDocument : public HTMLDocument {
 public:
  FileHTMLDocument();
  FileHTMLDocument(const std::string &pathToFile);
  FileHTMLDocument(const std::string &pathToFile, std::istream &fileToRead);
  ~FileHTMLDocument();
  FileHTMLDocument(const FileHTMLDocument &src);
  FileHTMLDocument &operator=(const FileHTMLDocument &src);

  std::string getData() const;
  std::size_t getSize() const;
  std::string getMimeType() const;
  std::string getLastModified() const;
  HTTPStatus::Status getStatus() const;

  std::string getPathToFile() const;

  void setFile(File *file);
  void setTime(Time *time);
  void setMimeType(GetMimeType *getMimeType);

 private:
  void init(const std::string &pathToFile, std::istream &fileToRead);

  void freeThings() const;

  HTTPStatus::Status _status;

  std::string _pathToFile;
  std::string _data;
  std::string _mimeType;
  std::string _lastModified;

  File *_file;
  Time *_time;
  GetMimeType *_getMimeType;
};

#endif