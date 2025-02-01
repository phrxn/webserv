#include "ErrorPageFileHTMLDocument.hpp"

ErrorPageFileHTMLDocument::ErrorPageFileHTMLDocument(){}

ErrorPageFileHTMLDocument::ErrorPageFileHTMLDocument(
    const std::string &pathToFile)
    : FileHTMLDocument(pathToFile) {}

ErrorPageFileHTMLDocument::ErrorPageFileHTMLDocument(
    const std::string &pathToFile, std::istream &fileToRead)
    : FileHTMLDocument(pathToFile, fileToRead) {}

ErrorPageFileHTMLDocument::~ErrorPageFileHTMLDocument() {}

ErrorPageFileHTMLDocument::ErrorPageFileHTMLDocument(
    const ErrorPageFileHTMLDocument &src)
    : FileHTMLDocument(src) {}

ErrorPageFileHTMLDocument &ErrorPageFileHTMLDocument::operator=(
    const ErrorPageFileHTMLDocument &src) {
  if (this == &src) return *this;
  FileHTMLDocument::operator=(src);
  return *this;
}

std::string ErrorPageFileHTMLDocument::getMimeType() const {
  return "text/html";
}

std::string ErrorPageFileHTMLDocument::getLastModified() const { return ""; }

HTMLDocument* ErrorPageFileHTMLDocument::clone() const{
	return new ErrorPageFileHTMLDocument(*this);
}