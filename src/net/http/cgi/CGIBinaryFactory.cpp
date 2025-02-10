#include "CGIBinaryFactory.hpp"

#include "../HTTPTypeOfPages.hpp"

CGIBinaryFactory::CGIBinaryFactory() {}

CGIBinaryFactory::~CGIBinaryFactory() {}

// delete, this class must be unique
CGIBinaryFactory::CGIBinaryFactory(const CGIBinaryFactory &src) { (void)src; }

// delete, this class must be unique
CGIBinaryFactory &CGIBinaryFactory::operator=(const CGIBinaryFactory &src) {
  (void)src;
  return *this;
}

CGIBinary CGIBinaryFactory::getCGIBinary(CGIBinary::SupportedCGI supportedCGI) {
  if (supportedCGI == CGIBinary::PHP) {
    return CGIBinary("/bin/php-cgi", CGIBinary::PHP);
  }
  return CGIBinary("/bin/python3", CGIBinary::PYTHON);
}

CGIBinary CGIBinaryFactory::getCGIBinary(const std::string &pathToScriptPath) {
  HTTPTypeOfPages typeOfPage;
  CGIBinary cgiBinary = getCGIBinary(typeOfPage.getStringToTypeOfPage(pathToScriptPath));
  cgiBinary.setPathToScriptToExecute(pathToScriptPath);
  return cgiBinary;
}

CGIBinary CGIBinaryFactory::getCGIBinary(
    HTTPTypeOfPages::TypeOfPage typeOfPage) {
  if (typeOfPage == HTTPTypeOfPages::PYTHON) {
    return getCGIBinary(CGIBinary::PHP);
  }
  if (typeOfPage == HTTPTypeOfPages::PYTHON) {
    return getCGIBinary(CGIBinary::PYTHON);
  }
  return CGIBinary("", CGIBinary::PHP);
}
