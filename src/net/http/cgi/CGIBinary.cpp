#include "CGIBinary.hpp"

CGIBinary::CGIBinary(std::string pathToFileToExecute, std::string pathToBinary,
                     SupportedCGI supportedFileType)
    :  _pathToBinary(pathToBinary),
	   _pathToFileToExecute(pathToFileToExecute),
       _supportedFileType(supportedFileType) {}

CGIBinary::CGIBinary(std::string pathToBinary, SupportedCGI supportedFileType)
    : _pathToBinary(pathToBinary),
	  _pathToFileToExecute(""),
      _supportedFileType(supportedFileType) {}

CGIBinary::~CGIBinary() {}

CGIBinary::CGIBinary(const CGIBinary &src)
    : _pathToBinary(src._pathToBinary),
	  _pathToFileToExecute(src._pathToFileToExecute),
      _supportedFileType(src._supportedFileType) {}

CGIBinary &CGIBinary::operator=(const CGIBinary &src) {
	if(this == &src) {
		return *this;
	}
	_pathToBinary = src._pathToBinary;
	_pathToFileToExecute = src._pathToFileToExecute;
	_supportedFileType = src._supportedFileType;
	return *this;
}

std::string CGIBinary::getPathToBinary() const {
	return _pathToBinary;
}

CGIBinary::SupportedCGI CGIBinary::getSupportedFileType() const {
	return _supportedFileType;
}

std::string CGIBinary::getPathToScriptToExecute() const {
	return _pathToFileToExecute;
}

void CGIBinary::setPathToScriptToExecute(const std::string &path) {
	_pathToFileToExecute = path;
}
