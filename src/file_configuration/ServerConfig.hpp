#ifndef FILE_CONFIGURATION_SERVER_CONFIG_HPP
#define FILE_CONFIGURATION_SERVER_CONFIG_HPP

#include <map>
#include <string>
#include <vector>

#include "CheckConfiguration.hpp"
#include "RouteConfig.hpp"

class ServerConfig : public CheckConfiguration{

public:
    ServerConfig(void);
	~ServerConfig();
	ServerConfig(const ServerConfig &src);
	ServerConfig &operator=(const ServerConfig &src);

	// Métodos de configuração
	void setPort(unsigned int port);
	void setHost(const std::string &host);
	void setServerName(const std::string &serverName);
	void setLimitBodySize(size_t limitBodySize);
	void addErrorPage(const std::string &errorPage, const std::string &errorPath);
	void addRoute(const RouteConfig &route);

	// Métodos de acesso
	unsigned int getPort(void) const;
	std::string getHost(void) const;
	std::string getServerName(void) const;
	size_t getLimitBodySize(void) const;
	const std::map<std::string, std::string> &getErrorPages(void) const;
	std::string getErrorPage(const std::string &errorPage) const;
	std::vector<RouteConfig> getRoutes(void) const;

	//inteface methods
	bool isPathValid(const URL& url) const;
    std::string isPathARedirection(const URL& url) const;
    bool isTheMethodAllowedForThisPath(const URL& url, HTTPMethods::Method method) const;
    bool isUrlAPathToCGI(const URL& url) const;
    std::string getThePhysicalPath(const URL& url) const;
    bool isDirectoryListingAllowedForThisPath(const URL& url) const;
    std::string getThePathToCustomPageForHTTPStatus(HTTPStatus::Status httpStatus) const;

private:
    unsigned int						_port; // Porta do servidor
    std::string							_host; // Endereço IP do servidor (localhost)
    std::string							_serverName; // Nome do servidor
    size_t								_limitBodySize; // Tamanho máximo do corpo da requisição
    std::map<std::string, std::string> 	_errorPages; // Mapa que armazena as páginas de erro
    std::vector<RouteConfig>			_routes; // Vetor que armazena as rotas configuradas
};

#endif