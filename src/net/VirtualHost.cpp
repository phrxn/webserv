#include "VirtualHost.hpp"

VirtualHost::~VirtualHost(){}

bool VirtualHost::isUrlAPathToCGI(std::string url) const{
	(void)url;
	return false;
}