#ifndef NET_HTTP_MIME_TYPE_HPP
#define NET_HTTP_MIME_TYPE_HPP

#include <map>
#include <string>

class GetMimeType {
 public:
  static void setMimetypeMap(const std::map<std::string, std::string> &mimeTypeMap);

  GetMimeType();
  ~GetMimeType();
  GetMimeType(const GetMimeType &src);
  GetMimeType &operator=(const GetMimeType &src);

  std::string getExtensionFromPath(const std::string &path) const;

  std::string getMimeTypeByFileExtesion(const std::string &fileExtension);

 private:
	static std::map<std::string, std::string> _mimeTypeMap;

};

#endif