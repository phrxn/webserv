#ifndef NET_VIRTUAL_HOST_DEFAULT_HPP
#define NET_VIRTUAL_HOST_DEFAULT_HPP

#include "VirtualHost.hpp"

class VirtualHostDefault : public VirtualHost {
 public:
  VirtualHostDefault();
  VirtualHostDefault(int port);
  VirtualHostDefault(int port, const std::string &serverName);
  ~VirtualHostDefault();
  VirtualHostDefault(const VirtualHostDefault &src);
  VirtualHostDefault &operator=(const VirtualHostDefault &src);
  bool operator==(const VirtualHostDefault &src) const;

  unsigned int getPort() const;
  void setPort(unsigned int port);
  std::string getServerName() const;
  void setServerName(const std::string &serverName);


 protected:
   unsigned int _port;
   std::string _serverName;
};

#endif