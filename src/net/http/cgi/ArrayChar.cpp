#include "ArrayChar.hpp"

#include <cstring>

ArrayChar::ArrayChar() {}

ArrayChar::~ArrayChar() {}

ArrayChar::ArrayChar(const ArrayChar &src) : _listOfString(src._listOfString) {}

ArrayChar &ArrayChar::operator=(const ArrayChar &src) {
  if (this == &src) return *this;
  _listOfString = src._listOfString;
  return *this;
}

bool ArrayChar::operator==(const ArrayChar &src) {
  if (this == &src) return true;
  if (_listOfString != src._listOfString) return false;
  return true;
}

void ArrayChar::addString(const std::string &stringToAdd) {
  _listOfString.push_back(stringToAdd);
}

// the called MUST free the pointer, see freePointerToArray
// if the ArrayChar is empty NULL is retorned
char **ArrayChar::getPointerToArray() const {
  if (_listOfString.empty()) {
    return NULL;
  }

  char **charArray = new char *[_listOfString.size() + 1];

  std::list<std::string>::const_iterator it = _listOfString.begin();
  std::list<std::string>::const_iterator end = _listOfString.end();

  int i = 0;
  for (; it != end; ++it) {
    const std::string &tempLine = *it;
    charArray[i] = new char[tempLine.size() + 1];
    std::strcpy(charArray[i], tempLine.c_str());
    ++i;
  }

  charArray[i] = NULL;

  return charArray;
}

// obviously the pointer and its contents MUST HAVE been mallocated previously
void ArrayChar::freePointerToArray(char **pointerToArray) {
  if (pointerToArray) {
    int i = 0;
    while (pointerToArray[i] != NULL) {
      delete[] pointerToArray[i];
      ++i;
    }
    delete[] pointerToArray;
  }
}

bool ArrayChar::compareCharArrays(const char *const *arr1,
                                  const char *const *arr2) {
  if ((arr1 == NULL && arr2 != NULL) || (arr1 != NULL && arr2 == NULL)) {
    return false;
  }
  if (arr1 == arr2) {
    return true;
  }

  int countElements = 0;
  for (;arr1[countElements] != NULL && arr2[countElements] != NULL; ++countElements) {
    if (std::string(arr1[countElements]) != std::string(arr2[countElements])) {
      return false;
    }
  }

  if ((arr1[countElements] == NULL && arr2[countElements] != NULL) ||
      (arr1[countElements] != NULL && arr2[countElements] == NULL)) {
    return false;
  }

  return true;
}