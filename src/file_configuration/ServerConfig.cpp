#include "ServerConfig.hpp"

// Construtor da estrutura ServerConfig
ServerConfig::ServerConfig(void) : VirtualHostDefault(8080), _limitBodySize(1000000) {}

ServerConfig::~ServerConfig(){}

ServerConfig::ServerConfig(const ServerConfig &src) : VirtualHostDefault(src){
	*this = src;
}

ServerConfig &ServerConfig::operator=(const ServerConfig &src){
	if (this == &src){return *this;}
	VirtualHostDefault::operator=(src);
    _host = src._host;
	_limitBodySize = src._limitBodySize;
    _errorPages = src._errorPages;
    _routes = src._routes;
	return *this;
}

// Métodos de configuração
void ServerConfig::setHost(const std::string &host){
	_host = host;
}

void ServerConfig::setLimitBodySize(size_t limitBodySize){
	_limitBodySize = limitBodySize;
}

void ServerConfig::addErrorPage(const std::string &errorPage, const std::string &errorPath){
	_errorPages[errorPage] = errorPath;
}

void ServerConfig::addRoute(const RouteConfig &route){
	_routes.push_back(route);
}

// Métodos de acesso
std::string ServerConfig::getHost(void) const{
	return _host;
}

size_t ServerConfig::getLimitBodySize(void) const{
	return _limitBodySize;
}

const std::map<std::string, std::string> &ServerConfig::getErrorPages(void) const{
	return _errorPages;
}

std::string ServerConfig::getErrorPage(const std::string &errorPage) const{
	std::map<std::string, std::string>::const_iterator it = _errorPages.find(errorPage);
	if (it != _errorPages.end()){
		return it->second;
	}
	return "";
}




std::vector<RouteConfig> ServerConfig::getRoutes(void) const{
	return _routes;
}

//inteface methods

bool ServerConfig::isPathValid(const URL& url) const {

	// Extrai o caminho da URL fornecida
	std::string path = url.getPath(true);
	// Itera sobre todas as rotas configuradas para o servidor atual

	for (std::vector<RouteConfig>::const_iterator route = _routes.begin(); route != _routes.end(); ++route) {
		// Verifica se o caminho da URL começa com o caminho da rota
		// Se encontrar uma correspondência, retorna true indicando que o caminho é válido
		if (path.find(route->getLocationPath()) == 0) {
			return true;
		}
	}

	// Se nenhuma correspondência for encontrada, retorna false indicando que o caminho não é válido
	return false;
}

std::string ServerConfig::isPathARedirection(const URL& url) const {

	// Extrai o caminho da URL fornecida
	std::string path = url.getPath(true);

	// Itera sobre todas as rotas configuradas para o servidor atual
	for (std::vector<RouteConfig>::const_iterator route = _routes.begin(); route != _routes.end(); ++route) {
		// Verifica se o caminho da URL começa com o caminho da rota e se a rota tem um redirecionamento configurado
		if (path.find(route->getLocationPath()) == 0 && route->getRedirectSet()) {
			// Retorna o caminho de redirecionamento configurado para a rota
			return route->getRedirect();
		}
	}

	// Se nenhuma correspondência for encontrada, retorna uma string vazia
	return "";
}

bool ServerConfig::isTheMethodAllowedForThisPath(const URL& url, HTTPMethods::Method method) const {
    // Extrai o caminho da URL fornecida
    std::string path = url.getPath(true);

	// Itera sobre todas as rotas configuradas para o servidor atual
	for (std::vector<RouteConfig>::const_iterator route = _routes.begin(); route != _routes.end(); ++route) {
		// Verifica se o caminho da URL começa com o caminho da rota
		if (path.find(route->getLocationPath()) == 0) {
			// Verifica se o método HTTP fornecido está na lista de métodos permitidos para a rota
			for (std::vector<HTTPMethods::Method>::const_iterator it = route->getMethods().begin(); it != route->getMethods().end(); ++it) {
				if (*it == method) {
					return true;
				}
			}
		}
	}

    // Se nenhuma correspondência for encontrada, retorna false indicando que o método não é permitido para o caminho
    return false;
}

bool ServerConfig::isUrlAPathToCGI(const URL& url) const {
	// Extrai o caminho da URL fornecida
	std::string path = url.getPath(true);

	// Itera sobre todas as rotas configuradas para o servidor atual
	for (std::vector<RouteConfig>::const_iterator route = _routes.begin(); route != _routes.end(); ++route) {
		// Verifica se o caminho da URL começa com o caminho da rota e se a rota tem o CGI habilitado
		if (path.find(route->getLocationPath()) == 0 && route->getCgiEnabled()) {
			// Retorna true indicando que o caminho aponta para um CGI
			return true;
		}
	}

	// Se nenhuma correspondência for encontrada, retorna false indicando que o caminho não aponta para um CGI
	return false;
}

std::string ServerConfig::getThePhysicalPath(const URL& url) const {
	// Extrai o caminho da URL fornecida
	std::string path = url.getPath(true);

	// Itera sobre todas as rotas configuradas para o servidor atual
	for (std::vector<RouteConfig>::const_iterator route = _routes.begin(); route != _routes.end(); ++route) {
		// Verifica se o caminho da URL começa com o caminho da rota
		if (path.find(route->getLocationPath()) == 0) {
			// Constrói o caminho físico concatenando o diretório raiz da rota com a parte do caminho da URL que vem após o caminho da rota
			std::string physicalPath = route->getRootDir() + path.substr(route->getLocationPath().length());
			// Retorna o caminho físico construído
			return physicalPath;
		}
	}

	// Se nenhuma correspondência for encontrada, retorna o caminho original da URL
	return path;
}

bool ServerConfig::isDirectoryListingAllowedForThisPath(const URL& url) const {
	// Extrai o caminho da URL fornecida
	std::string path = url.getPath(true);

	// Itera sobre todas as rotas configuradas para o servidor atual
	for (std::vector<RouteConfig>::const_iterator route = _routes.begin(); route != _routes.end(); ++route) {
		// Verifica se o caminho da URL começa com o caminho da rota e se a listagem de diretório está habilitada para a rota
		if (path.find(route->getLocationPath()) == 0 && route->getAutoindex()) {
			// Retorna true indicando que a listagem de diretório está habilitada para o caminho
			return true;
		}
	}

	// Se nenhuma correspondência for encontrada, retorna false indicando que a listagem de diretório não está habilitada para o caminho
	return false;
}

std::string ServerConfig::getThePathToCustomPageForHTTPStatus(HTTPStatus::Status httpStatus) const {

	// Converte o código de status HTTP para uma string usando HTTPStatus::getStatusToString
	HTTPStatus status;
	std::string statusCode = status.getStatusToString(httpStatus);

	// Procura o código de status HTTP nas páginas de erro configuradas para o servidor atual
	std::map<std::string, std::string>::const_iterator it = _errorPages.find(statusCode);
	// Se encontrar uma correspondência, retorna o caminho da página de erro personalizada
	if (it != _errorPages.end()) {
		return it->second;
	}

	// Se nenhuma correspondência for encontrada, retorna uma string vazia
	return "";
}
