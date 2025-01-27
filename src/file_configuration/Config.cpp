// #include "Config.hpp"
// #include "Define.hpp"

// // Construtor da estrutura RouteConfig
// RouteConfig::RouteConfig(void)
// {
// 	methods.push_back(GET);
// 	locationPath = DEFAULT_LOCATION_PATH;
// 	rootDir = DEFAULT_ROOT_DIR;
// 	indexFile = DEFAULT_INDEX_FILE;
// 	redirect = DEFAULT_EMPTY;
// 	uploadPath = DEFAULT_UPLOAD_PATH;
// 	autoindex = false;
// 	uploadEnabled = false;
// 	rootSet = false;
// 	redirectSet = false;
// 	cgiEnabled = DEFAULT_EMPTY;
// 	cgiPath = DEFAULT_EMPTY;
// 	cgiExtension = false;
// }

// // Construtor da estrutura ServerConfig
// ServerConfig::ServerConfig(void)
// {
// 	port = DEFAULT_PORT;
// 	host = DEFAULT_HOST;
// 	serverName = DEFAULT_SERVER_NAME;
// 	limitBodySize = DEFAULT_LIMIT_BODY_SIZE;
// 	errorPages["400"] = DEFAULT_ERROR_PAGE_400;
// 	errorPages["401"] = DEFAULT_ERROR_PAGE_401;
// 	errorPages["403"] = DEFAULT_ERROR_PAGE_403;
// 	errorPages["404"] = DEFAULT_ERROR_PAGE_404;
// 	errorPages["405"] = DEFAULT_ERROR_PAGE_405;
// 	errorPages["500"] = DEFAULT_ERROR_PAGE_500;
// 	errorPages["501"] = DEFAULT_ERROR_PAGE_501;
// 	errorPages["505"] = DEFAULT_ERROR_PAGE_505;
// }

// // Construtor da classe Config
// Config::Config(const std::string &fileName) : _configFile(fileName)
// {
// 	std::ifstream configFile(fileName.c_str());

// 	if (!configFile.is_open() || configFile.fail())
// 	{
// 		throw std::runtime_error("Could Not Open Log File!");
// 	}

// 	if (configFile.peek() == std::ifstream::traits_type::eof())
// 	{
// 		throw std::runtime_error("Config File Is Empty!");
// 	}

// 	if (configFile.is_open())
// 	{
// 		_countServer = ConfigUtils::getServerCount(fileName);
// 		_parseConfigFile(configFile); // metodo publico para chamar a struct ServerConfig
// 		configFile.close();
// 		return;
// 	}
// };

// // Destructor da classe Config
// Config::~Config(void) {};

// // Função auxiliar para verificar se a linha inicia um bloco de servidor
// bool isServerBlockStart(const std::string &line)
// {
// 	if (line.find("server_name") == std::string::npos && line.find("server") != std::string::npos)
// 	{
// 		size_t serverEndPos = line.find("server") + std::string("server").length();
// 		while (serverEndPos <= line.length() && std::isspace(line[serverEndPos]))
// 		{
// 			serverEndPos++;
// 		}
// 		if (serverEndPos <= line.length() &&
// 			(line[serverEndPos] == '{' || line[serverEndPos] == '\0'))
// 		{
// 			return true;
// 		}
// 	}
// 	return false;
// }

// // Método publico que lê o arquivo de configuração (configFile) e inicia o processo de interpretação das configurações contidas nele.
// void Config::_parseConfigFile(std::ifstream &configFile)
// {
// 	// Declaração de variáveis locais
// 	std::string line;				// Armazena cada linha lida do arquivo de configuração
// 	std::string serverBlock;		// Armazena o bloco de configuração do servidor
// 	bool insideServerBlock = false; // Indica se estamos dentro de um bloco de servidor
// 	int braceCount = 0;				// Conta o número de chaves '{' e '}' para verificar a integridade do bloco

// 	// Lê o arquivo linha por linha
// 	while (std::getline(configFile, line))
// 	{
// 		// Verifica se a linha inicia um bloco de servidor
// 		if (isServerBlockStart(line))
// 		{
// 			insideServerBlock = true;
// 		}

// 		// Se estamos dentro de um bloco de servidor
// 		if (insideServerBlock)
// 		{
// 			// Adiciona a linha atual ao bloco de servidor
// 			serverBlock += line + std::string("\n");
// 			// Itera sobre cada caractere da linha
// 			for (std::string::iterator it = line.begin(); it != line.end(); ++it)
// 			{
// 				char chr = *it;
// 				// Incrementa braceCount se encontrar '{'
// 				if (chr == '{')
// 				{
// 					braceCount++;
// 				}
// 				// Decrementa braceCount se encontrar '}'
// 				else if (chr == '}')
// 				{
// 					braceCount--;

// 					// Se braceCount ficar negativo, lança uma exceção
// 					if (braceCount < 0)
// 					{
// 						throw std::runtime_error("ERROR_INVALID_SERVER");
// 					}
// 				}
// 			}
// 			// Se braceCount for 0, significa que o bloco de servidor está completo
// 			if (braceCount == 0)
// 			{
// 				// Verifica se o bloco contém "server" mas não contém "{"
// 				if (serverBlock.find("server") != std::string::npos &&
// 					serverBlock.find("{") == std::string::npos)
// 				{
// 					continue; // Continua para a próxima iteração do loop
// 				}
// 				// Reseta braceCount e insideServerBlock
// 				braceCount = 0;
// 				insideServerBlock = false;
// 				// Chama o método _parseServerBlock para processar o bloco de servidor
// 				_parseServerBlock(serverBlock);
// 				// Limpa o conteúdo de serverBlock
// 				serverBlock.clear();
// 			}
// 		}
// 	}
// 	// Se braceCount não for 0, lança uma exceção
// 	if (braceCount != 0)
// 	{
// 		throw std::runtime_error("ERROR_INVALID_SERVER");
// 	}
// }

// void Config::_parseServerBlock(const std::string &serverBlock)
// {
//     std::string trimBlock = ConfigUtils::trim(serverBlock);
//     std::istringstream serverStream(trimBlock);
//     std::set<std::string> serverKeys;
//     ServerConfig server;
//     std::string line;

//     while (std::getline(serverStream, line))
//     {
// 		if (!line.empty() && (line[line.size() - 1] != '[' && line[line.size() - 1] != ']') &&
//             (line.empty() || line[line.size() - 1] != ';'))
//         {
//             throw std::runtime_error("ERROR_INVALID_LINE");
//         }
//         std::istringstream tokenStream(line);
//         std::string token;
//         std::vector<std::string> tokens;

//         while (tokenStream >> token)
//         {
//             if (!token.empty() && token[token.size() - 1] == ';')
//             {
//                 token = token.substr(0, token.size() - 1);
//             }
//             tokens.push_back(token);
//         }

//         if (tokens.empty())
//         {
//             continue;
//         }

//         if (tokens[0] != "error_page" && tokens[0] != "location" &&
//             serverKeys.find(tokens[0]) != serverKeys.end())
//         {
//             throw std::runtime_error("ERROR_DUPLICATE_KEY");
//         }
//         else
//         {
//             serverKeys.insert(tokens[0]);
//         }

//         if (tokens[0] == "listen")
//         {
//             ServerExtraction::extractPort(tokens, server);
//         }
//         else if (tokens[0] == "host")
//         {
//             ServerExtraction::extractHost(tokens, server);
//         }
//         else if (tokens[0] == "server_name")
//         {
//             ServerExtraction::extractServerName(tokens, server);
//         }
//         else if (tokens[0] == "limit_body_size")
//         {
//             ServerExtraction::extractLimitBodySize(tokens, server);
//         }
//         else if (tokens[0] == "error_page")
//         {
//             ServerExtraction::extractErrorPages(tokens, server);
//         }
//         else if (tokens[0] == "location")
//         {
//             if (tokens[1].empty() || tokens.size() != 2 || tokens[1] != "[")
//             {
//                 throw std::runtime_error("ERROR_INVALID_LOCATION");
//             }
//             else
//             {
//                 _parseRouteStream(serverStream, server);
//             }
//         }
//         else
//         {
//             throw std::runtime_error("ERROR_INVALID_KEY");
//         }
//     }
//     _servers.push_back(server);
// }

// void Config::_parseRouteStream(std::istringstream &serverStream, ServerConfig &server) {
//     std::string line; // Armazena cada linha lida do stream
//     std::string locationBlock; // Armazena o bloco de configuração da localização
//     RouteConfig location; // Estrutura para armazenar as configurações da localização
//     int locationBracketsCount = 1; // Conta o número de colchetes ']' para verificar a integridade do bloco
//     bool insideLocationBlock = true; // Indica se estamos dentro de um bloco de localização

//     // Lê o stream linha por linha
//     while (std::getline(serverStream, line)) {
//         if (insideLocationBlock) {
//             // Se a linha não contém ']', adiciona ao bloco de localização
//             if (line.find("]") == std::string::npos) {
//                 locationBlock += line + std::string("\n");
//             }
//             // Itera sobre cada caractere da linha
//             for (std::string::iterator it = line.begin(); it != line.end(); ++it) {
//                 char chr = *it;
//                 // Decrementa locationBracketsCount se encontrar ']'
//                 if (chr == ']') {
//                     locationBracketsCount--;

//                     // Se locationBracketsCount ficar negativo, lança uma exceção
//                     if (locationBracketsCount < 0) {
//                         throw std::runtime_error(ERROR_INVALID_LOCATION);
//                     }
//                 }
//             }
//             // Se locationBracketsCount for 0, significa que o bloco de localização está completo
//             if (locationBracketsCount == 0) {
//                 locationBracketsCount = 0;
//                 insideLocationBlock = false;
//                 // Chama o método _parseRouteBlock para processar o bloco de localização
//                 _parseRouteBlock(locationBlock, location);
//                 // Adiciona a configuração da localização ao vetor de localizações do servidor
//                 server.routes.push_back(location);
//                 locationBlock.clear();
//                 return;
//             }
//         }
//     }
//     // Se locationBracketsCount não for 0, lança uma exceção
//     if (locationBracketsCount != 0) {
//         throw std::runtime_error(ERROR_INVALID_LOCATION);
//     }
// }

// void Config::_parseRouteBlock(const std::string &locationBlock, RouteConfig &location) {
//     // Cria um stream de entrada a partir do bloco de localização
//     std::istringstream locationStream(locationBlock);
//     // Conjunto para armazenar as chaves da localização e verificar duplicatas
//     std::set<std::string> locationKeys;
//     // String para armazenar cada linha lida do stream
//     std::string line;

//     // Lê o stream linha por linha
//     while (std::getline(locationStream, line)) {
//         // Verifica se a linha está vazia ou não termina com ';'
//         if (line.empty() || line[line.size() - 1] != ';') {
//             throw std::runtime_error(ERROR_INVALID_LINE);
//         }
//         // Cria um stream de entrada a partir da linha
//         std::istringstream tokenStream(line);
//         // String para armazenar cada token
//         std::string token;
//         // Vetor para armazenar todos os tokens da linha
//         std::vector<std::string> tokens;

//         // Lê o stream de tokens palavra por palavra
//         while (tokenStream >> token) {
//             // Remove o ponto e vírgula do final do token, se houver
//             if (!token.empty() && token[token.size() - 1] == ';') {
//                 token = token.substr(0, token.size() - 1);
//             }
//             // Adiciona o token ao vetor de tokens
//             tokens.push_back(token);
//         }

//         // Se não houver tokens, continua para a próxima iteração do loop
//         if (tokens.empty()) {
//             continue;
//         }

//         // Verifica se a chave do token já existe
//         if (locationKeys.find(tokens[0]) != locationKeys.end()) {
//             throw std::runtime_error(ERROR_DUPLICATE_KEY);
//         } else {
//             // Adiciona a chave ao conjunto de chaves da localização
//             locationKeys.insert(tokens[0]);
//         }

//         // Processa o token com base na chave
//         if (tokens[0] == "methods") {
//             RouteExtraction::extractMethods(tokens, location);
//         } else if (tokens[0] == "location_path") {
//             RouteExtraction::extractLocationPath(tokens, location);
//         } else if (tokens[0] == "root") {
//             RouteExtraction::extractRootDir(tokens, location);
//         } else if (tokens[0] == "index") {
//             RouteExtraction::extractIndexFile(tokens, location);
//         } else if (tokens[0] == "redirect") {
//             RouteExtraction::extractRedirect(tokens, location);
//         } else if (tokens[0] == "upload_path") {
//             RouteExtraction::extractUploadPath(tokens, location);
//         } else if (tokens[0] == "autoindex") {
//             RouteExtraction::extractAutoindex(tokens, location);
//         } else if (tokens[0] == "upload_enabled") {
//             RouteExtraction::extractUploadEnabled(tokens, location);
//         } else if (tokens[0] == "cgi_path") {
//             RouteExtraction::extractCGIPath(tokens, location);
//         } else if (tokens[0] == "cgi_extension") {
//             RouteExtraction::extractCGIExtension(tokens, location);
//         } else {
//             throw std::runtime_error(ERROR_INVALID_KEY);
//         }
//     }
//     // Valida o caminho completo da localização
//     ConfigUtils::validateFullLocationPath(location);
//     // Valida o caminho completo do CGI
//     ConfigUtils::validateFullCGIPath(location);
//     // Cria a pasta de upload, se necessário
//     ConfigUtils::createUploadFolder(location.uploadPath);
// }

// // Método público para obter os servidores
// std::vector<ServerConfig> Config::getServers(void) const
// {
//     return this->_servers;
// }


#include "Config.hpp"
#include "Define.hpp"

// Construtor da estrutura RouteConfig
RouteConfig::RouteConfig(void)
{
    methods.push_back(GET);
    locationPath = DEFAULT_LOCATION_PATH;
    rootDir = DEFAULT_ROOT_DIR;
    indexFile = DEFAULT_INDEX_FILE;
    redirect = DEFAULT_EMPTY;
    uploadPath = DEFAULT_UPLOAD_PATH;
    autoindex = false;
    uploadEnabled = false;
    rootSet = false;
    redirectSet = false;
    cgiEnabled = false;
    cgiPath = DEFAULT_EMPTY;
    cgiExtension = DEFAULT_EMPTY;
}

// Construtor da estrutura ServerConfig
ServerConfig::ServerConfig(void)
{
    port = DEFAULT_PORT;
    host = DEFAULT_HOST;
    serverName = DEFAULT_SERVER_NAME;
    limitBodySize = DEFAULT_LIMIT_BODY_SIZE;
    errorPages["400"] = DEFAULT_ERROR_PAGE_400;
    errorPages["401"] = DEFAULT_ERROR_PAGE_401;
    errorPages["403"] = DEFAULT_ERROR_PAGE_403;
    errorPages["404"] = DEFAULT_ERROR_PAGE_404;
    errorPages["405"] = DEFAULT_ERROR_PAGE_405;
    errorPages["500"] = DEFAULT_ERROR_PAGE_500;
    errorPages["501"] = DEFAULT_ERROR_PAGE_501;
    errorPages["505"] = DEFAULT_ERROR_PAGE_505;
}

// Construtor da classe Config
Config::Config(const std::string &fileName) : _configFile(fileName)
{
    std::ifstream configFile(fileName.c_str());

    if (!configFile.is_open() || configFile.fail())
    {
        throw std::runtime_error("Could Not Open Log File!");
    }

    if (configFile.peek() == std::ifstream::traits_type::eof())
    {
        throw std::runtime_error("Config File Is Empty!");
    }

    if (configFile.is_open())
    {
        _countServer = ConfigUtils::getServerCount(fileName);
        _parseConfigFile(configFile);
        configFile.close();
        return;
    }
}

// Destructor da classe Config
Config::~Config(void) {}

// Função auxiliar para verificar se a linha inicia um bloco de servidor
bool isServerBlockStart(const std::string &line)
{
    if (line.find("server_name") == std::string::npos && line.find("server") != std::string::npos)
    {
        size_t serverEndPos = line.find("server") + std::string("server").length();
        while (serverEndPos <= line.length() && std::isspace(line[serverEndPos]))
        {
            serverEndPos++;
        }
        if (serverEndPos <= line.length() &&
            (line[serverEndPos] == '{' || line[serverEndPos] == '\0'))
        {
            return true;
        }
    }
    return false;
}

// Método público que lê o arquivo de configuração (configFile) e inicia o processo de interpretação das configurações contidas nele.
void Config::_parseConfigFile(std::ifstream &configFile)
{
    std::string line;
    std::string serverBlock;
    bool insideServerBlock = false;
    int braceCount = 0;

    while (std::getline(configFile, line))
    {
        if (isServerBlockStart(line))
        {
            insideServerBlock = true;
        }

        if (insideServerBlock)
        {
            serverBlock += line + std::string("\n");
            for (std::string::iterator it = line.begin(); it != line.end(); ++it)
            {
                char chr = *it;
                if (chr == '{')
                {
                    braceCount++;
                }
                else if (chr == '}')
                {
                    braceCount--;

                    if (braceCount < 0)
                    {
                        throw std::runtime_error("ERROR_INVALID_SERVER");
                    }
                }
            }
            if (braceCount == 0)
            {
                if (serverBlock.find("server") != std::string::npos &&
                    serverBlock.find("{") == std::string::npos)
                {
                    continue;
                }
                braceCount = 0;
                insideServerBlock = false;
                _parseServerBlock(serverBlock);
                serverBlock.clear();
            }
        }
    }
    if (braceCount != 0)
    {
        throw std::runtime_error("ERROR_INVALID_SERVER");
    }
}

void Config::_parseServerBlock(const std::string &serverBlock)
{
    std::string trimmedBlock = ConfigUtils::trim(serverBlock);
    std::istringstream serverStream(trimmedBlock);
    std::set<std::string> serverKeys;
    ServerConfig server;
    std::string line;

    while (std::getline(serverStream, line))
    {
        if (!line.empty() && (line[line.size() - 1] != '[' && line[line.size() - 1] != ']') &&
            (line.empty() || line[line.size() - 1] != ';'))
        {
            throw std::runtime_error("ERROR_INVALID_LINE");
        }
        std::istringstream tokenStream(line);
        std::string token;
        std::vector<std::string> tokens;

        while (tokenStream >> token)
        {
            if (!token.empty() && token[token.size() - 1] == ';')
            {
                token = token.substr(0, token.size() - 1);
            }
            tokens.push_back(token);
        }

        if (tokens.empty())
        {
            continue;
        }

        if (tokens[0] != "error_page" && tokens[0] != "location" &&
            serverKeys.find(tokens[0]) != serverKeys.end())
        {
            throw std::runtime_error("ERROR_DUPLICATE_KEY");
        }
        else
        {
            serverKeys.insert(tokens[0]);
        }

        if (tokens[0] == "listen")
        {
            ServerExtraction::extractPort(tokens, server);
        }
        else if (tokens[0] == "host")
        {
            ServerExtraction::extractHost(tokens, server);
        }
        else if (tokens[0] == "server_name")
        {
            ServerExtraction::extractServerName(tokens, server);
        }
        else if (tokens[0] == "limit_body_size")
        {
            ServerExtraction::extractLimitBodySize(tokens, server);
        }
        else if (tokens[0] == "error_page")
        {
            ServerExtraction::extractErrorPages(tokens, server);
        }
        else if (tokens[0] == "location")
        {
            if (tokens.size() < 2 || tokens[1].empty() || tokens[1] != "[")
            {
                throw std::runtime_error("ERROR_INVALID_LOCATION");
            }
            else
            {
                _parseRouteStream(serverStream, server);
            }
        }
        else
        {
            throw std::runtime_error("ERROR_INVALID_KEY");
        }
    }
    _servers.push_back(server);
}

void Config::_parseRouteStream(std::istringstream &serverStream, ServerConfig &server)
{
    std::string line;
    std::string locationBlock;
    RouteConfig location;
    int locationBracketsCount = 1;
    bool insideLocationBlock = true;

    while (std::getline(serverStream, line))
    {
        if (insideLocationBlock)
        {
            if (line.find("]") == std::string::npos)
            {
                locationBlock += line + std::string("\n");
            }
            for (std::string::iterator it = line.begin(); it != line.end(); ++it)
            {
                char chr = *it;
                if (chr == ']')
                {
                    locationBracketsCount--;

                    if (locationBracketsCount < 0)
                    {
                        throw std::runtime_error("ERROR_INVALID_LOCATION");
                    }
                }
            }
            if (locationBracketsCount == 0)
            {
                locationBracketsCount = 0;
                insideLocationBlock = false;
                _parseRouteBlock(locationBlock, location);
                server.routes.push_back(location);
                locationBlock.clear();
                return;
            }
        }
    }
    if (locationBracketsCount != 0)
    {
        throw std::runtime_error("ERROR_INVALID_LOCATION");
    }
}

void Config::_parseRouteBlock(const std::string &locationBlock, RouteConfig &location)
{
    std::istringstream locationStream(locationBlock);
    std::set<std::string> locationKeys;
    std::string line;

    while (std::getline(locationStream, line))
    {
        if (line.empty() || line[line.size() - 1] != ';')
        {
            throw std::runtime_error("ERROR_INVALID_LINE");
        }
        std::istringstream tokenStream(line);
        std::string token;
        std::vector<std::string> tokens;

        while (tokenStream >> token)
        {
            if (!token.empty() && token[token.size() - 1] == ';')
            {
                token = token.substr(0, token.size() - 1);
            }
            tokens.push_back(token);
        }

        if (tokens.empty())
        {
            continue;
        }

        if (locationKeys.find(tokens[0]) != locationKeys.end())
        {
            throw std::runtime_error("ERROR_DUPLICATE_KEY");
        }
        else
        {
            locationKeys.insert(tokens[0]);
        }

        if (tokens[0] == "methods")
        {
            RouteExtraction::extractMethods(tokens, location);
        }
        else if (tokens[0] == "location_path")
        {
            RouteExtraction::extractLocationPath(tokens, location);
        }
        else if (tokens[0] == "root")
        {
            RouteExtraction::extractRootDir(tokens, location);
        }
        else if (tokens[0] == "index")
        {
            RouteExtraction::extractIndexFile(tokens, location);
        }
        else if (tokens[0] == "redirect")
        {
            RouteExtraction::extractRedirect(tokens, location);
        }
        else if (tokens[0] == "upload_path")
        {
            RouteExtraction::extractUploadPath(tokens, location);
        }
        else if (tokens[0] == "autoindex")
        {
            RouteExtraction::extractAutoindex(tokens, location);
        }
        else if (tokens[0] == "upload_enabled")
        {
            RouteExtraction::extractUploadEnabled(tokens, location);
        }
        else if (tokens[0] == "cgi_path")
        {
            RouteExtraction::extractCGIPath(tokens, location);
        }
        else if (tokens[0] == "cgi_extension")
        {
            RouteExtraction::extractCGIExtension(tokens, location);
        }
        else
        {
            throw std::runtime_error("ERROR_INVALID_KEY");
        }
    }
    ConfigUtils::validateFullLocationPath(location);
    ConfigUtils::validateFullCGIPath(location);
    ConfigUtils::createUploadFolder(location.uploadPath);
}

// Método público para obter os servidores
std::vector<ServerConfig> Config::getServers(void) const
{
    return this->_servers;
}