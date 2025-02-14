#ifndef START_CREATE_LOADER_VIRTUAL_HOST_HPP
#define START_CREATE_LOADER_VIRTUAL_HOST_HPP

#include <vector>

#include "../net/VirtualHostDefault.hpp"
#include "../error/StatusOr.hpp"

class LoaderVirtualHost {
 public:
   virtual ~LoaderVirtualHost();
   virtual error::StatusOr<std::vector<VirtualHostDefault *> >loadVirtualHosts() = 0;
};

#endif