#ifndef START_CREATE_LOADER_VIRTUAL_HOST_FAKE_HPP
#define START_CREATE_LOADER_VIRTUAL_HOST_FAKE_HPP

#include "LoaderVirtualHost.hpp"

class LoaderVirtualHostFake : public LoaderVirtualHost {
 public:
  LoaderVirtualHostFake();
  ~LoaderVirtualHostFake();
  LoaderVirtualHostFake(const LoaderVirtualHostFake &src);
  LoaderVirtualHostFake &operator=(const LoaderVirtualHostFake &src);

  error::StatusOr<std::vector<VirtualHostDefault *> > loadVirtualHosts();
};

#endif