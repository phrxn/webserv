#ifndef NET_HTTP_CGI_ARRAY_CHAR_HPP
#define NET_HTTP_CGI_ARRAY_CHAR_HPP

#include <list>
#include <string>

class ArrayChar {
 public:
  ArrayChar();
  ~ArrayChar();
  ArrayChar(const ArrayChar &src);
  ArrayChar &operator=(const ArrayChar &src);
  bool operator==(const ArrayChar &src);

  void addString(const std::string &stringToAdd);

  // the called MUST free the pointer, see freePointerToArray
  char **getPointerToArray() const;

  // obviously the pointer and its contents MUST HAVE been mallocated previously
  void freePointerToArray(char **pointerToArray);

  bool compareCharArrays(const char* const* arr1, const char* const* arr2);

 private:
  std::list<std::string> _listOfString;
};

#endif