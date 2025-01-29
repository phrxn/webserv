#ifndef NET_HTTP_HTML_ERROR_PAGE_FILE_HTML_DOCUMENT_HPP
#define NET_HTTP_HTML_ERROR_PAGE_FILE_HTML_DOCUMENT_HPP

#include <string>

#include "FileHTMLDocument.hpp"

class ErrorPageFileHTMLDocument : public FileHTMLDocument {
 public:
  ErrorPageFileHTMLDocument();
  ErrorPageFileHTMLDocument(const std::string &pathToFile);
  ErrorPageFileHTMLDocument(const std::string &pathToFile, std::istream &fileToRead);
  ~ErrorPageFileHTMLDocument();
  ErrorPageFileHTMLDocument(const ErrorPageFileHTMLDocument &src);
  ErrorPageFileHTMLDocument &operator=(const ErrorPageFileHTMLDocument &src);

  std::string getMimeType() const;
  std::string getLastModified() const;

};

#endif