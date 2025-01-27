#ifndef NET_HTTP_DEFAULT_ERROR_PAGE_HPP
#define NET_HTTP_DEFAULT_ERROR_PAGE_HPP

#include <string>

class DefaultErrorPage {
 public:
  DefaultErrorPage();
  DefaultErrorPage(const std::string &data);
  ~DefaultErrorPage();
  DefaultErrorPage(const DefaultErrorPage &src);
  DefaultErrorPage &operator=(const DefaultErrorPage &src);

  std::string getData() const;
  std::string::size_type getSize() const;

 private:
  std::string _data;
  std::string::size_type _size;

};

#endif