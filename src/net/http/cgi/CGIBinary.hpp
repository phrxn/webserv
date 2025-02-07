#ifndef NET_HTTP_CGI_CGI_BINARY_HPP
#define NET_HTTP_CGI_CGI_BINARY_HPP

#include <string>

#include "../HTTPTypeOfPages.hpp"

class CGIBinary {
 public:
  enum SupportedCGI { PHP, PYTHON };
  CGIBinary(std::string pathToFileToExecute, std::string pathToBinary, SupportedCGI supportedFileType);
  CGIBinary(std::string pathToBinary, SupportedCGI supportedFileType);
  virtual ~CGIBinary();
  CGIBinary(const CGIBinary &other);
  CGIBinary &operator=(const CGIBinary &other);

  std::string getPathToBinaryExecutable() const;

  SupportedCGI getSupportedFileType() const;

  std::string getPathToScriptToExecute() const;

  void setPathToScriptToExecute(const std::string &path);

  private:
    std::string _pathToFileToExecute;
	std::string _pathToBinary;
	CGIBinary::SupportedCGI _supportedFileType;

};

#endif