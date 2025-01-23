#ifndef NET_VIRTUAL_HOST_HPP
#define NET_VIRTUAL_HOST_HPP

#include <string>

class VirtualHost {
 public:
  VirtualHost();
  VirtualHost(int port, const std::string &serverName);
  virtual ~VirtualHost();
  VirtualHost(const VirtualHost &src);
  VirtualHost &operator=(const VirtualHost &src);
  bool operator==(const VirtualHost &src) const;

  virtual bool isUrlAPathToCGI(std::string url) const;
  virtual int getPort() const;
  virtual void setPort(int port);
  virtual std::string getServername() const;
  virtual void setServername(const std::string &serverName);

 private:
  int _port;
  std::string _serverName;
};

#endif