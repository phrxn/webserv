#include "Config.hpp"
#include "Define.hpp"
#include <filesystem>

/* Server Extraction Functions */
namespace ServerExtraction
{

	// Função para verificar se o token é válido e não está vazio
	void validateToken(const std::vector<std::string> &tokens, size_t index, const std::string &errorMessage)
	{
		if (tokens.size() <= index || tokens[index].empty())
		{
			throw std::runtime_error(errorMessage);
		}
	}

	// Função para extrair e validar a porta do servidor
	void extractPort(std::vector<std::string> &tokens, ServerConfig &server)
	{
		validateToken(tokens, 1, ERROR_MISSING_VALUE);

		std::stringstream stringPort(tokens[1]);
		long long portValue;

		if (stringPort >> portValue)
		{
			if (portValue > std::numeric_limits<unsigned short>::max() || portValue < 1024)
			{
				throw std::runtime_error(ERROR_INVALID_PORT);
			}
			server.port = static_cast<unsigned short>(portValue);
		}
		else
		{
			throw std::runtime_error(ERROR_INVALID_PORT);
		}
	}

	   void extractHost(std::vector<std::string> &tokens, ServerConfig &server)
	{
		validateToken(tokens, 1, ERROR_MISSING_VALUE);
		server.host = tokens[1];
	}

	// Função para extrair e definir o nome do servidor
	void extractServerName(std::vector<std::string> &tokens, ServerConfig &server)
	{
		validateToken(tokens, 1, ERROR_MISSING_VALUE);
		server.serverName = tokens[1];
	}

	// Função para extrair e definir o limite de tamanho do corpo da requisição
	void extractLimitBodySize(std::vector<std::string> &tokens, ServerConfig &server)
	{
		validateToken(tokens, 1, ERROR_MISSING_VALUE);

		std::stringstream stringSize(tokens[1]);
		size_t limitBodySizeMB;

		if (stringSize >> limitBodySizeMB)
		{
			server.limitBodySize = limitBodySizeMB * 1024 * 1024;
			if (tokens[1][0] == '-')
			{
				throw std::runtime_error(ERROR_INVALID_LIMIT_BODY_SIZE);
			}
		}
		else
		{
			throw std::runtime_error(ERROR_INVALID_LIMIT_BODY_SIZE);
		}
	}

	// Função para extrair e validar as páginas de erro do servidor
	void extractErrorPages(std::vector<std::string> &tokens, ServerConfig &server)
	{
		validateToken(tokens, 1, ERROR_MISSING_VALUE);
		validateToken(tokens, 2, ERROR_MISSING_VALUE);

		std::string errorCode = tokens[1];
		std::string fileName = tokens[2];
		ConfigUtils::formatPath(fileName);
		std::ifstream file(fileName.c_str());

		if (!file.is_open() || file.fail())
		{
			throw std::runtime_error(ERROR_INVALID_ERROR_PAGE);
		}
		else
		{
			server.errorPages[errorCode] = fileName;
		}
	}
}

/* Location Extraction Functions */
namespace RouteExtraction
{

	// Função para validar se o token está presente e não está vazio
	void validateToken(const std::vector<std::string> &tokens, size_t index, const std::string &errorMessage)
	{
		if (tokens.size() <= index || tokens[index].empty())
		{
			throw std::runtime_error(errorMessage);
		}
	}

	// Função para extrair e validar os métodos permitidos na localização
	void extractMethods(std::vector<std::string> &tokens, RouteConfig &location)
	{
		validateToken(tokens, 1, ERROR_MISSING_VALUE);
		location.methods.clear();

		for (std::vector<std::string>::iterator it = tokens.begin() + 1; it != tokens.end(); ++it)
		{
			std::transform(it->begin(), it->end(), it->begin(), ::toupper);
			if (*it == "GET" && !ConfigUtils::isRepeatedMethod(location.methods, GET))
			{
				location.methods.push_back(GET);
			}
			else if (*it == "POST" && !ConfigUtils::isRepeatedMethod(location.methods, POST))
			{
				location.methods.push_back(POST);
			}
			else if (*it == "DELETE" && !ConfigUtils::isRepeatedMethod(location.methods, DELETE))
			{
				location.methods.push_back(DELETE);
			}
			else
			{
				throw std::runtime_error(ERROR_INVALID_METHOD);
			}
		}
	}

	// Função para extrair e definir o caminho da localização
	void extractLocationPath(std::vector<std::string> &tokens, RouteConfig &location)
	{
		validateToken(tokens, 1, ERROR_MISSING_VALUE);
		location.locationPath = tokens[1];
	}

	// Função para extrair e definir o diretório raiz da localização
	void extractRootDir(std::vector<std::string> &tokens, RouteConfig &location)
	{
		validateToken(tokens, 1, ERROR_MISSING_VALUE);
		std::string rootPath = tokens[1];
		ConfigUtils::formatPath(rootPath);

		if (!ConfigUtils::directoryExists(rootPath))
		{
			throw std::runtime_error(ERROR_INVALID_ROOT);
		}   
		else
		{
			location.rootDir = rootPath;
			location.rootSet = true;
		}
	}

	// Função para extrair e definir o índice da localização
	void extractIndexFile(std::vector<std::string> &tokens, RouteConfig &location)
	{
		validateToken(tokens, 1, ERROR_MISSING_VALUE);
		location.indexFile = tokens[1];
	}

	// Função para extrair e definir o redirecionamento da localização
	void extractRedirect(std::vector<std::string> &tokens, RouteConfig &location)
	{
		validateToken(tokens, 1, ERROR_MISSING_VALUE);
		location.redirect = tokens[1];
		location.redirectSet = true;
	}

	// Função para extrair e definir o caminho de upload da localização
	void extractUploadPath(std::vector<std::string> &tokens, RouteConfig &location)
	{
		validateToken(tokens, 1, ERROR_MISSING_VALUE);
		ConfigUtils::formatPath(tokens[1]);
		location.uploadPath = tokens[1];
	}

	// Função para extrair e definir o autoindex da localização
	void extractAutoindex(std::vector<std::string> &tokens, RouteConfig &location)
	{
		validateToken(tokens, 1, ERROR_MISSING_VALUE);
		std::transform(tokens[1].begin(), tokens[1].end(), tokens[1].begin(), ::tolower);
		if (tokens[1] == "on")
		{
			location.autoindex = true;
		}
		else
		{
			throw std::runtime_error(ERROR_INVALID_AUTOINDEX);
		}
	}

	// Função para extrair e definir se o upload está habilitado na localização
	void extractUploadEnabled(std::vector<std::string> &tokens, RouteConfig &location)
	{
		validateToken(tokens, 1, ERROR_MISSING_VALUE);
		if (tokens[1] == "on")
		{
			location.uploadEnabled = true;
		}
		else
		{
			throw std::runtime_error(ERROR_INVALID_UPLOAD_ENABLED);
		}
	}

	// Função para extrair e definir o caminho do CGI na localização
	void extractCGIPath(std::vector<std::string> &tokens, RouteConfig &location)
	{
		validateToken(tokens, 1, ERROR_MISSING_VALUE);
		std::string cgiPath = tokens[1];
		size_t lastDot = cgiPath.find_last_of('.');

		if (lastDot != std::string::npos &&
			(cgiPath.substr(lastDot) == EXTENSION_PHP || cgiPath.substr(lastDot) == EXTENSION_PY))
		{
			location.cgiEnabled = true;
			location.cgiPath = cgiPath;
		}
		else
		{
			throw std::runtime_error(ERROR_INVALID_CGI_PATH);
		}
	}

	// Função para extrair e definir a extensão do CGI na localização
	void extractCGIExtension(std::vector<std::string> &tokens, RouteConfig &location)
	{
		validateToken(tokens, 1, ERROR_MISSING_VALUE);
		std::string cgiExtension = tokens[1];

		if (cgiExtension == EXTENSION_PHP || cgiExtension == EXTENSION_PY)
		{
			location.cgiEnabled = true;
			location.cgiExtension = cgiExtension;
		}
		else
		{
			throw std::runtime_error(ERROR_INVALID_CGI_EXTENSION);
		}
	}
}