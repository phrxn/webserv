#ifndef NET_HTTP_HTML_CREATE_DIRECTORY_HTML_PAGE_HPP
#define NET_HTTP_HTML_CREATE_DIRECTORY_HTML_PAGE_HPP

#include <list>
#include <string>

#include "ItemDirectoryHTMLDocument.hpp"

class CreateDirectoryHTMLPage {
 public:
  CreateDirectoryHTMLPage(const std::string& directoryPath, const std::string &urlPathToDir);
  ~CreateDirectoryHTMLPage();
  CreateDirectoryHTMLPage(const CreateDirectoryHTMLPage& src);
  CreateDirectoryHTMLPage& operator=(const CreateDirectoryHTMLPage& src);

  CreateDirectoryHTMLPage& operator<<(const ItemDirectoryHTMLDocument& item);

  std::string createAnchorToPath(const ItemDirectoryHTMLDocument& item) const;

  std::string formatPath(const ItemDirectoryHTMLDocument& item) const;

  std::string formatData(const ItemDirectoryHTMLDocument& item) const;

  std::string str();

  std::string getBody() const;

  void setBody(const std::string& body);

 private:
  std::string _directoryPath;
  std::string _urlPathToDir;
  std::string _body;
  std::list<std::string> _paths;
};

#endif