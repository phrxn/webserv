#ifndef NET_HTTP_MIME_TYPE_HPP
#define NET_HTTP_MIME_TYPE_HPP

#include <map>
#include <string>

class MimeType {
 public:
  static void setMimetypeMap(const std::map<std::string, std::string> &mimeTypeMap);

  MimeType();
  ~MimeType();
  MimeType(const MimeType &src);
  MimeType &operator=(const MimeType &src);

  std::string getExtensionFromPath(const std::string &path) const;

  std::string getMimeTypeByFileExtesion(const std::string &fileExtension);

 private:
	static std::map<std::string, std::string> _mimeTypeMap;

};

#endif