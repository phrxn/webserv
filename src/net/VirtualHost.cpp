#include "VirtualHost.hpp"

VirtualHost::~VirtualHost(){}

bool VirtualHost::isUrlAPathToCGI(std::string url) const{
	(void)url;
	return false;
}

int VirtualHost::getPort() const{
	return 80;
}

std::string VirtualHost::getHostName() const{
	return "";
}