#include "FileHTMLDocument.hpp"

#include <sstream>

FileHTMLDocument::FileHTMLDocument(): _status(HTTPStatus::NOT_FOUND),
      _file(new File),
      _time(new Time),
      _getMimeType(new GetMimeType) {
}

FileHTMLDocument::FileHTMLDocument(const std::string &pathToFile)
    : _status(HTTPStatus::NOT_FOUND),
      _file(new File(pathToFile)),
      _time(new Time),
      _getMimeType(new GetMimeType) {

	std::ifstream file(pathToFile.c_str());
	init(pathToFile, file);

}

FileHTMLDocument::FileHTMLDocument(const std::string &pathToFile,
                                   std::istream &fileToRead)
    : _status(HTTPStatus::NOT_FOUND),
      _file(new File(pathToFile)),
      _time(new Time),
      _getMimeType(new GetMimeType) {

	init(pathToFile, fileToRead);
}

FileHTMLDocument::~FileHTMLDocument() {
	freeThings();
}

FileHTMLDocument::FileHTMLDocument(const FileHTMLDocument &src):
	  _status(src._status),
      _file(new File(*src._file)),
      _time(new Time(*src._time)),
      _getMimeType(new GetMimeType(*src._getMimeType)) {

	_pathToFile = src._pathToFile;
	_data = src._data;
	_mimeType = src._mimeType;
	_lastModified = src._lastModified;
}

FileHTMLDocument &FileHTMLDocument::operator=(const FileHTMLDocument &src) {
	if (this == &src) return *this;
	freeThings();

	_status = src._status;
    _file = new File(*src._file);
    _time = new Time(*src._time);
    _getMimeType = new GetMimeType(*src._getMimeType);

	_pathToFile = src._pathToFile;
	_data = src._data;
	_mimeType = src._mimeType;
	_lastModified = src._lastModified;

	return *this;
}

std::string FileHTMLDocument::getData() const {
	return _data;
}

std::size_t FileHTMLDocument::getSize() const {
	return _data.size();
}

std::string FileHTMLDocument::getMimeType() const {
	return _mimeType;
}

std::string FileHTMLDocument::getLastModified() const {
	return _lastModified;
}

HTTPStatus::Status FileHTMLDocument::getStatus() const{
	return _status;
}

std::string FileHTMLDocument::getPathToFile() const {
	return _pathToFile;
}

void FileHTMLDocument::setFile(File *file) {
  if (_file) {
    delete _file;
  }
  _file = file;
}

void FileHTMLDocument::setTime(Time *time) {
  if (_time) {
    delete _time;
  }
  _time = time;
}

void FileHTMLDocument::setMimeType(GetMimeType *getMimeType) {
  if (_getMimeType) {
    delete _getMimeType;
  }
  _getMimeType = getMimeType;
}

void FileHTMLDocument::init(const std::string &pathToFile,
                            std::istream &fileToRead) {
  _pathToFile = pathToFile;
  _data = "";
  _mimeType = "";
  _lastModified = "";

  if (!fileToRead.good()) {
    return;
  }

  _status = HTTPStatus::OK;

  std::stringstream ss;
  ss << fileToRead.rdbuf();

  _data = ss.str();
  _mimeType = _getMimeType->getExtensionFromPath(pathToFile);
  _lastModified =
      _time->convertTimeToHTTPHeaderPattern(_file->getModificationTime());
}

void FileHTMLDocument::freeThings() const{
  if (_file) {
    delete _file;
  }
  if (_time) {
    delete _time;
  }
  if (_getMimeType) {
    delete _getMimeType;
  }
}