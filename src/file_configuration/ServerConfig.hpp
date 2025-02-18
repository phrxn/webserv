#ifndef FILE_CONFIGURATION_SERVER_CONFIG_HPP
#define FILE_CONFIGURATION_SERVER_CONFIG_HPP

#include <map>
#include <string>
#include <vector>

#include "../net/VirtualHostDefault.hpp"
#include "RouteConfig.hpp"

class ServerConfig : public VirtualHostDefault{

public:
    ServerConfig(void);
	~ServerConfig();
	ServerConfig(const ServerConfig &src);
	ServerConfig &operator=(const ServerConfig &src);

	// Métodos de configuração
	void setHost(const std::string &host);
	void setLimitBodySize(size_t limitBodySize);
	void addErrorPage(const std::string &errorPage, const std::string &errorPath);
	void addRoute(const RouteConfig &route);

	// Métodos de acesso
	std::string getHost(void) const;
	const std::map<std::string, std::string> &getErrorPages(void) const;
	std::string getErrorPage(const std::string &errorPage) const;
	std::vector<RouteConfig> getRoutes(void) const;

	//utils
	std::vector<RouteConfig>::const_iterator getMatchedRouteConfig(const std::vector<RouteConfig> &_routes, const std::string &path) const;

	//inteface methods

	bool isPathValid(const URL& url) const;
    std::string isPathARedirection(const URL& url) const;
    bool isTheMethodAllowedForThisPath(const URL& url, HTTPMethods::Method method) const;
    bool isUrlAPathToCGI(const URL& url) const;
    std::string getThePhysicalPath(const URL& url) const;
	std::string getTheRelativePhysicalPath(const URL& url) const;
    bool isDirectoryListingAllowedForThisPath(const URL& url) const;
    std::string getThePathToCustomPageForHTTPStatus(HTTPStatus::Status httpStatus) const;
	std::string getRootDir(const URL& url) const;
	std::string getIndexFile(const URL& url) const;
	size_t getLimitBodySizeInBytes(void) const;

	// Return the upload folder full path
	//
	// a empty string is returned if the upload folder is not set (or upload is off)
	// or the path points to a CGI
	std::string getUploadFolderPath(const URL& url) const;

private:
    std::string							_host; // Endereço IP do servidor (localhost)
    size_t								_limitBodySize; // Tamanho máximo do corpo da requisição
    std::map<std::string, std::string> 	_errorPages; // Mapa que armazena as páginas de erro
    std::vector<RouteConfig>			_routes; // Vetor que armazena as rotas configuradas
};

#endif