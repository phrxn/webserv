#ifndef NET_HTTP_HTTP_TYPE_OF_PAGES_HPP
#define NET_HTTP_HTTP_TYPE_OF_PAGES_HPP

#include <map>
#include <string>

class HTTPTypeOfPages {
 public:
  enum TypeOfPage { STATIC, PHP, PYTHON };

  HTTPTypeOfPages();
  ~HTTPTypeOfPages();
  HTTPTypeOfPages(const HTTPTypeOfPages &src);
  HTTPTypeOfPages &operator=(const HTTPTypeOfPages &src);

  HTTPTypeOfPages::TypeOfPage getStringToTypeOfPageFromPath(const std::string &path) const;
  HTTPTypeOfPages::TypeOfPage getStringToTypeOfPage(const std::string &typeOfPage) const ;
  std::string getTypeOfPageToString(HTTPTypeOfPages::TypeOfPage typeOfPage) const ;
  HTTPTypeOfPages::TypeOfPage getTypeOfPathFromPath(const std::string &path) const ;

 private:
  static const std::map<HTTPTypeOfPages::TypeOfPage, std::string> mapTypeOfPage;
  static std::map<HTTPTypeOfPages::TypeOfPage, std::string> startMapTypeOfPage();
};

#endif
