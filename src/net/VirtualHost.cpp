#include "VirtualHost.hpp"

VirtualHost::~VirtualHost(){}

bool VirtualHost::isUrlAPathToCGI(std::string url) const{
	(void)url;
	return false;
}

std::string VirtualHost::getScriptExtension() const{
	return ".php";
}

std::string VirtualHost::getRootFolder() const{
	return "/var/www/html";
}