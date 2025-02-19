#ifndef FILE_CONFIGURATION_CONFIG_HPP
#define FILE_CONFIGURATION_CONFIG_HPP

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <limits>	 // Limites numéricos
#include <algorithm> // Funções de algoritmo
#include <cctype>	 // Funções de caracteres
#include <set>		 // Conjuntos
#include <sys/stat.h>
#include <sys/types.h>


#include "../net/http/HTTPMethods.hpp"
#include "ServerConfig.hpp"

class Config {
    private:
            short						_countServer; // Índice do servidor atual
            const std::string			_configFile; // Caminho do arquivo de configuração (nome do arquivo)
            std::vector<ServerConfig>	_servers; // Vetor que armazena as configurações dos servidores

            // Métodos privados
            void	_parseConfigFile(std::ifstream &configFile); // é um método que lê o arquivo de configuração (configFile) e inicia o processo de interpretação das configurações contidas nele.
            void	_parseServerBlock(const std::string &serverBlock); // processa cada "bloco" de configuração de servidor (serverBlock). Esse bloco define as configurações de um servidor específico.
            void	_parseRouteStream(std::istringstream &serverStream, ServerConfig &server ); // analisa as configurações de localização de um servidor específico (server). Usa um istringstream para ler o bloco de configurações e atribuir valores apropriados ao servidor.
            void	_parseRouteBlock(const std::string &locationBlock, RouteConfig &location); // processa cada "bloco" de configuração de localização (locationBlock). Esse bloco define as configurações de uma rota específica.

    public:
            // Construtor
            Config(const std::string &configFile); // Construtor da classe Config

            // Destrutor
            ~Config(void); // Destrutor da classe Config

            // Métodos públicos
            std::vector<ServerConfig>		getServers(void) const; // Retorna o vetor de servidores
};

//config utils functions
namespace ConfigUtils {
    short			getServerCount(const std::string &configFile); // Retorna o número de servidores configurados
    std::string		trim(const std::string &serverBlock); // Remove espaços em branco do início e do final de uma strin
    bool			isRepeatedMethod(const std::vector<HTTPMethods::Method> &methodsVector, HTTPMethods::Method method); // Verifica se um método HTTP já foi configurado
    bool			directoryExists(const std::string &path); // Verifica se um diretório existe
    bool			fileExists(const std::string &path); // Verifica se um arquivo existe
	bool			pathEndsWithSlash(const std::string &path); // Verifica se o caminho termina com uma barra
    void			printServerStruct(const ServerConfig &server); // Imprime a estrutura do servidor
}

//Server Extraction functions
namespace ServerExtraction {
    void			extractPort(std::vector<std::string> &tokens, ServerConfig &server); // Extrai a porta do servidor
    void			extractHost(std::vector<std::string> &tokens, ServerConfig &server); // Extrai o host do servidor
    void			extractServerName(std::vector<std::string> &tokens, ServerConfig &server); // Extrai o nome do servidor
    void			extractLimitBodySize(std::vector<std::string> &tokens, ServerConfig &server); // Extrai o tamanho máximo do corpo da requisição
    void			extractErrorPages(std::vector<std::string> &tokens, ServerConfig &server); // Extrai as páginas de erro
}

//Route Extraction functions
namespace RouteExtraction {
    void			extractMethods(std::vector<std::string> &tokens, RouteConfig &location); // Extrai os métodos HTTP permitidos
    void			extractLocationPath(std::vector<std::string> &tokens, RouteConfig &location); // Extrai o caminho da rota
    void			extractRootDir(std::vector<std::string> &tokens, RouteConfig &location); // Extrai o diretório raiz
    void			extractIndexFile(std::vector<std::string> &tokens, RouteConfig &location); // Extrai o arquivo de índice
    void			extractRedirect(std::vector<std::string> &tokens, RouteConfig &location); // Extrai a URL de redirecionamento
	void			extractAutoindex(std::vector<std::string> &tokens, RouteConfig &location); // Extrai o autoindex
    void			extractUploadPath(std::vector<std::string> &tokens, RouteConfig &location); // Extrai o caminho de upload
    void			extractUploadEnabled(std::vector<std::string> &tokens, RouteConfig &location); // Extrai o upload habilitado
    void			extractCGIPath(std::vector<std::string> &tokens, RouteConfig &location); // Extrai o caminho do CGI
    void			extractCGIEnable(std::vector<std::string> &tokens, RouteConfig &location); // Extrai o CGI habilitado
}

typedef std::map<std::string, std::string> errorMap;

#endif