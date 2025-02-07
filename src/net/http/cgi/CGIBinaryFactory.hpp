#ifndef NET_HTTP_CGI_CGI_BINARY_FACTORY_HPP
#define NET_HTTP_CGI_CGI_BINARY_FACTORY_HPP

#include <string>

#include "CGIBinary.hpp"
#include "../HTTPTypeOfPages.hpp"

class CGIBinaryFactory {
 public:
  CGIBinaryFactory();
  ~CGIBinaryFactory();
  CGIBinary getCGIBinary(CGIBinary::SupportedCGI supportedCGI);
  CGIBinary getCGIBinary(const std::string &pathToScriptPath);
  CGIBinary getCGIBinary(HTTPTypeOfPages::TypeOfPage typeOfPage);

 private:
  CGIBinaryFactory(const CGIBinaryFactory &src);
  CGIBinaryFactory &operator=(const CGIBinaryFactory &src);
};

#endif
