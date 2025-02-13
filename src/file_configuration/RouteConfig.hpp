#ifndef FILE_CONFIGURATION_ROUTE_CONFIG_HPP
#define FILE_CONFIGURATION_ROUTE_CONFIG_HPP

#include <string>
#include <vector>

#include "../net/http/HTTPMethods.hpp"

class RouteConfig {
public:
	RouteConfig(void);
	~RouteConfig(void);
	RouteConfig(const RouteConfig &src);
	RouteConfig &operator=(const RouteConfig &src);

	// Métodos públicos
	const std::vector<HTTPMethods::Method>	&getMethods(void) const; // Retorna os métodos HTTP permitidos
	std::string							getLocationPath(void) const; // Retorna o caminho da rota
	std::string							getRootDir(void) const; // Retorna o diretório raiz
	std::string							getIndexFile(void) const; // Retorna o arquivo de índice
	std::string							getRedirect(void) const; // Retorna a URL de redirecionamento
	std::string							getUploadPath(void) const; // Retorna o caminho de upload
	bool								getAutoindex(void) const; // Retorna o valor da flag autoindex
	bool								getUploadEnabled(void) const; // Retorna o valor da flag uploadEnabled
	bool								getRootSet(void) const; // Retorna o valor da flag rootSet
	bool								getRedirectSet(void) const; // Retorna o valor da flag redirectSet
	bool								getCgiEnabled(void) const; // Retorna o valor da flag cgiEnabled
	std::string							getCgiPath(void) const; // Retorna o caminho do script CGI
	std::string							getCgiExtension(void) const; // Retorna a extensão do script CGI
	void								addMethod(const HTTPMethods::Method &method);

	void	setMethods(const std::vector<HTTPMethods::Method> &methods); // Define os métodos HTTP permitidos
	void	setLocationPath(const std::string &locationPath); // Define o caminho da rota
	void	setRootDir(const std::string &rootDir); // Define o diretório raiz
	void	setIndexFile(const std::string &indexFile); // Define o arquivo de índice
	void	setRedirect(const std::string &redirect); // Define a URL de redirecionamento
	void	setUploadPath(const std::string &uploadPath); // Define o caminho de upload
	void	setAutoindex(const bool &autoindex); // Define o valor da flag autoindex
	void	setUploadEnabled(const bool &uploadEnabled); // Define o valor da flag uploadEnabled
	void	setRootSet(const bool &rootSet); // Define o valor da flag rootSet
	void	setRedirectSet(const bool &redirectSet); // Define o valor da flag redirectSet
	void	setCgiEnabled(const bool &cgiEnabled); // Define o valor da flag cgiEnabled
	void	setCgiPath(const std::string &cgiPath); // Define o caminho do script CGI
	void	setCgiExtension(const std::string &cgiExtension); // Define a extensão do script CGI
	void	clearMethods(void); // Limpa o vetor de métodos


private:
    std::vector<HTTPMethods::Method>	_methods; // Vetor que armazena os métodos HTTP permitidos (GET, POST, DELETE)
    std::string				_locationPath; // Caminho da rota
    std::string				_rootDir; // Diretório raiz da rota
    std::string				_indexFile; // Nome do arquivo de índice (por exemplo, index.html)
    std::string				_redirect; // URL para redirecionamento, se aplicável
    std::string				_uploadPath; // Caminho onde os arquivos enviados serão armazenados
    bool					_autoindex; // Flag que indica se o autoindex está habilitado
    bool					_uploadEnabled; // Flag que indica se o upload de arquivos está habilitado
    bool					_rootSet; // Flag que indica se o diretório raiz foi configurado
    bool					_redirectSet; // Flag que indica se o redirecionamento foi configurado
    bool					_cgiEnabled; // Flag que indica se o CGI está habilitado
    std::string				_cgiPath; // Caminho para o script CGI
    std::string				_cgiExtension; // Extensão de arquivo para scripts CGI
};

#endif