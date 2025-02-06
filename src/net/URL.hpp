#ifndef NET_HTTP_URL_HPP
#define NET_HTTP_URL_HPP

#include <string>
#include "http/HTTPTypeOfPages.hpp"

class HTTPTypeOfPages;

class URL {
 public:
  URL();
  URL(const std::string &urlEncoded);
  ~URL();
  URL(const URL &src);

  URL &operator=(const URL &src);
  bool operator==(const URL &src) const;

  const std::string &getProtocol() const;
  void setProtocol(const std::string &protocol);

  int getPort() const;
  void setPort(int port);

  const std::string &getDomain() const;
  void setDomain(const std::string &domain);

  void setPathFull(const std::string &path);
  std::string getPathFull(bool decoded) const;
  std::string getPath(bool decoded) const;
  std::string getExtraPathFromFullPath(bool decoded) const;

  const std::string &getQuery() const;
  void setQuery(const std::string &query);

  void parserStringToURL(std::string url);

  std::string extractProtocol(std::string &url);
  std::string extractDomain(std::string &url);
  std::string extractPort(std::string &url);
  std::string extractPath(std::string &url);
  std::string extractQuery(std::string &url);

  std::string decode(const std::string &input) const;
  std::string removePathToExtraPath(const std::string& str, HTTPTypeOfPages::TypeOfPage typeOfPage) const;

 private:
  static const std::string PROTOCOL_DELIMITER;
  static const std::string PORT_DELIMITER;
  static const std::string PATH_DELIMITER;
  static const std::string QUERY_DELIMITER;

  bool isHexDigit(char c) const;
  char hexToChar(const std::string &hex) const;

  std::string _protocol;
  std::string _domain;
  int _port;
  std::string _path;
  std::string _query;
  HTTPTypeOfPages _httpTypeOfPages;
};

std::ostream &operator<<(std::ostream &os, const URL &url);

#endif