#include "LoaderVirtualHostFake.hpp"

#include <vector>

#include "../net/VirtualHostFake.hpp"

LoaderVirtualHostFake::LoaderVirtualHostFake(){}

LoaderVirtualHostFake::~LoaderVirtualHostFake(){}

LoaderVirtualHostFake::LoaderVirtualHostFake(const LoaderVirtualHostFake &src){
	(void)src;
}

LoaderVirtualHostFake &LoaderVirtualHostFake::operator=(const LoaderVirtualHostFake &src){
	(void)src;
	return *this;
}

error::StatusOr<std::vector<VirtualHostDefault *> > LoaderVirtualHostFake::loadVirtualHosts(){

	std::vector<VirtualHostDefault *> virtualHostsFromFile;
	VirtualHostFake *a = new VirtualHostFake(8111, "ha");
	VirtualHostFake *b = new VirtualHostFake(8111, "hb");
	VirtualHostFake *c = new VirtualHostFake(8110, "ha");

	virtualHostsFromFile.push_back(a);
	virtualHostsFromFile.push_back(b);
	virtualHostsFromFile.push_back(c);

	return virtualHostsFromFile;
}