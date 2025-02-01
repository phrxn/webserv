#ifndef NET_HTTP_HTML_ITEM_DIRECTORY_HTML_DOCUMENT_HPP
#define NET_HTTP_HTML_ITEM_DIRECTORY_HTML_DOCUMENT_HPP

#include <string>

#include "../../../io/File.hpp"
#include "../../../time/Time.hpp"

class ItemDirectoryHTMLDocument {
 public:
  //ItemDirectoryHTMLDocument();
  ItemDirectoryHTMLDocument(const File &file, const std::string &dirParent);
  ItemDirectoryHTMLDocument(const std::string &path, time_t modificationTime,
                            ssize_t sizeInBytes, bool isDirectory);
  ~ItemDirectoryHTMLDocument();
  ItemDirectoryHTMLDocument(const ItemDirectoryHTMLDocument &src);
  ItemDirectoryHTMLDocument &operator=(const ItemDirectoryHTMLDocument &src);
  bool operator==(const ItemDirectoryHTMLDocument &src);
  bool operator<(const ItemDirectoryHTMLDocument &src);

  std::string getPath() const;
  std::string getModificationTime() const;
  std::string getSizeInBytes() const;
  bool isDirectory() const;

 private:
  void init(const std::string &path, time_t modificationTime,
            ssize_t sizeInBytes, bool isDirectory);

  std::string _dirParent;
  std::string _path;
  time_t _modificationTime;
  ssize_t _sizeInBytes;
  bool _isDirectory;
  Time _time;
};

#endif