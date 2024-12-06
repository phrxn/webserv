#ifndef NET_VIRTUAL_HOST_HPP
#define NET_VIRTUAL_HOST_HPP

#include <string>

class VirtualHost {
 public:
  virtual ~VirtualHost();
  virtual bool isUrlAPathToCGI(std::string url) const;
};

#endif