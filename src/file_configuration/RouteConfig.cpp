#include "RouteConfig.hpp"

// Construtor da estrutura RouteConfig
RouteConfig::RouteConfig(void)
    : _autoindex(false),
      _uploadEnabled(false),
      _rootSet(false),
      _redirectSet(false),
      _cgiEnabled(false) {}

RouteConfig::~RouteConfig(void) {}

RouteConfig::RouteConfig(const RouteConfig &src) { *this = src; }

RouteConfig &RouteConfig::operator=(const RouteConfig &src) {
  if (this == &src) {
    return *this;
  }
  _methods = src._methods;
  _locationPath = src._locationPath;
  _rootDir = src._rootDir;
  _indexFile = src._indexFile;
  _redirect = src._redirect;
  _uploadPath = src._uploadPath;
  _autoindex = src._autoindex;
  _uploadEnabled = src._uploadEnabled;
  _rootSet = src._rootSet;
  _redirectSet = src._redirectSet;
  _cgiEnabled = src._cgiEnabled;
  _cgiPath = src._cgiPath;
  return *this;
}

const std::vector<HTTPMethods::Method> &RouteConfig::getMethods(void) const { return _methods;}

std::string RouteConfig::getLocationPath(void) const { return _locationPath; }

std::string RouteConfig::getRootDir(void) const { return _rootDir; }

std::string RouteConfig::getIndexFile(void) const { return _indexFile; }

std::string RouteConfig::getRedirect(void) const { return _redirect; }

std::string RouteConfig::getUploadPath(void) const { return _uploadPath; }

bool RouteConfig::getAutoindex(void) const { return _autoindex; }

bool RouteConfig::getUploadEnabled(void) const { return _uploadEnabled; }

bool RouteConfig::getRootSet(void) const { return _rootSet; }

bool RouteConfig::getRedirectSet(void) const { return _redirectSet; }

bool RouteConfig::getCgiEnabled(void) const { return _cgiEnabled; }

std::string RouteConfig::getCgiPath(void) const { return _cgiPath; }

void RouteConfig::addMethod(const HTTPMethods::Method &method){
	_methods.push_back(method);
}

void RouteConfig::setMethods(const std::vector<HTTPMethods::Method> &methods) {
  _methods = methods;
}

void RouteConfig::setLocationPath(const std::string &locationPath) {
  _locationPath = locationPath;
}

void RouteConfig::setRootDir(const std::string &rootDir) { _rootDir = rootDir; }

void RouteConfig::setIndexFile(const std::string &indexFile) {
  _indexFile = indexFile;
}

void RouteConfig::setRedirect(const std::string &redirect) {
  _redirect = redirect;
}

void RouteConfig::setUploadPath(const std::string &uploadPath) {
  _uploadPath = uploadPath;
}

void RouteConfig::setAutoindex(const bool &autoindex) {
  _autoindex = autoindex;
}

void RouteConfig::setUploadEnabled(const bool &uploadEnabled) {
  _uploadEnabled = uploadEnabled;
}

void RouteConfig::setRootSet(const bool &rootSet) { _rootSet = rootSet; }

void RouteConfig::setRedirectSet(const bool &redirectSet) {
  _redirectSet = redirectSet;
}

void RouteConfig::setCgiEnabled(const bool &cgiEnabled){
	_cgiEnabled = cgiEnabled;
}
void RouteConfig::setCgiPath(const std::string &cgiPath){
	_cgiPath = cgiPath;
}

void RouteConfig::clearMethods(void){
	_methods.clear();
}