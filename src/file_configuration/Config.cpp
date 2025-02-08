
#include "Config.hpp"
#include "Define.hpp"

// Construtor da estrutura RouteConfig
RouteConfig::RouteConfig(void)
    : autoindex(false), uploadEnabled(false), rootSet(false), redirectSet(false), cgiEnabled(false) {}

// Construtor da estrutura ServerConfig
// ServerConfig::ServerConfig(void)
// {
//     port = DEFAULT_PORT;
//     host = DEFAULT_HOST;
//     serverName = DEFAULT_SERVER_NAME;
//     limitBodySize = DEFAULT_LIMIT_BODY_SIZE;
//     errorPages["400"] = DEFAULT_ERROR_PAGE_400;
//     errorPages["401"] = DEFAULT_ERROR_PAGE_401;
//     errorPages["403"] = DEFAULT_ERROR_PAGE_403;
//     errorPages["404"] = DEFAULT_ERROR_PAGE_404;
//     errorPages["405"] = DEFAULT_ERROR_PAGE_405;
//     errorPages["500"] = DEFAULT_ERROR_PAGE_500;
//     errorPages["501"] = DEFAULT_ERROR_PAGE_501;
//     errorPages["505"] = DEFAULT_ERROR_PAGE_505;
// }

ServerConfig::ServerConfig(void) : port(8080), limitBodySize(1000000) {}

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
}

// Método público para obter os servidores
std::vector<ServerConfig> Config::getServers(void) const
{
    return this->_servers;
}

bool Config::isPathValid(const URL& url) const {
    // Extrai o caminho da URL fornecida
    std::string path = url.getPath();
    // Itera sobre todos os servidores configurados
    for (const auto& server : _servers) {
        // Itera sobre todas as rotas configuradas para o servidor atual
        for (const auto& route : server.routes) {
            // Verifica se o caminho da URL começa com o caminho da rota
            // Se encontrar uma correspondência, retorna true indicando que o caminho é válido
            if (path.find(route.locationPath) == 0) {
                return true;
            }
        }
    }
     // Se nenhuma correspondência for encontrada, retorna false indicando que o caminho não é válido
    return false;
}

std::string Config::isPathARedirection(const URL& url) const {
    // Extrai o caminho da URL fornecida
    std::string path = url.getPath();
    // Itera sobre todos os servidores configurados
    for (const auto& server : _servers) {
        // Itera sobre todas as rotas configuradas para o servidor atual
        for (const auto& route : server.routes) {
            // Verifica se o caminho da URL começa com o caminho da rota e se a rota tem um redirecionamento configurado
            if (path.find(route.locationPath) == 0 && route.redirectSet) {
                // Retorna o caminho de redirecionamento configurado para a rota
                return route.redirect;
            }
        }
    }
    // Se nenhuma correspondência for encontrada, retorna uma string vazia
    return "";
}

bool Config::isTheMethodAllowedForThisPath(const URL& url, HTTPMethods::Method method) const {
    // Extrai o caminho da URL fornecida
    std::string path = url.getPath();
     // Itera sobre todos os servidores configurados
    for (const auto& server : _servers) {
        // Itera sobre todas as rotas configuradas para o servidor atual
        for (const auto& route : server.routes) {
            // Verifica se o caminho da URL começa com o caminho da rota
            if (path.find(route.locationPath) == 0) {
                // Verifica se o método HTTP fornecido está na lista de métodos permitidos para a rota
                return std::find(route.methods.begin(), route.methods.end(), method) != route.methods.end();
            }
        }
    }
    // Se nenhuma correspondência for encontrada, retorna false indicando que o método não é permitido para o caminho
    return false;
}

bool Config::isUrlAPathToCGI(const URL& url) const {
    // Extrai o caminho da URL fornecida
    std::string path = url.getPath();
    // Extrai o caminho da URL fornecida
    for (const auto& server : _servers) {
        // Itera sobre todas as rotas configuradas para o servidor atual
        for (const auto& route : server.routes) {
            // Verifica se o caminho da URL começa com o caminho da rota e se a rota tem o CGI habilitado
            if (path.find(route.locationPath) == 0 && route.cgiEnabled) {
                // Retorna true indicando que o caminho aponta para um CGI
                return true;
            }
        }
    }
    // Se nenhuma correspondência for encontrada, retorna false indicando que o caminho não aponta para um CGI
    return false;
}

std::string Config::getThePhysicalPath(const URL& url) const {
    // Extrai o caminho da URL fornecida
    std::string path = url.getPath();
    // Itera sobre todos os servidores configurados
    for (const auto& server : _servers) {
        // Itera sobre todas as rotas configuradas para o servidor atual
        for (const auto& route : server.routes) {
            // Verifica se o caminho da URL começa com o caminho da rota
            if (path.find(route.locationPath) == 0) {
                // Constrói o caminho físico concatenando o diretório raiz da rota com a parte do caminho da URL que vem após o caminho da rota
                std::string physicalPath = route.rootDir + path.substr(route.locationPath.length());
                // Retorna o caminho físico construído
                return physicalPath;
            }
        }
    }
    // Se nenhuma correspondência for encontrada, retorna o caminho original da URL
    return path;
}

bool Config::isDirectoryListingAllowedForThisPath(const URL& url) const {
    // Extrai o caminho da URL fornecida
    std::string path = url.getPath();
    // Itera sobre todos os servidores configurados
    for (const auto& server : _servers) {
        // Itera sobre todas as rotas configuradas para o servidor atual
        for (const auto& route : server.routes) {
            // Verifica se o caminho da URL começa com o caminho da rota e se a listagem de diretório está habilitada para a rota
            if (path.find(route.locationPath) == 0 && route.autoindex) {
                // Retorna true indicando que a listagem de diretório está habilitada para o caminho
                return true;
            }
        }
    }
    // Se nenhuma correspondência for encontrada, retorna false indicando que a listagem de diretório não está habilitada para o caminho
    return false;
}

std::string Config::getThePathToCustomPageForHTTPStatus(HTTPStatus::Status httpStatus) const {
    // Converte o código de status HTTP para uma string
    std::string statusCode = std::to_string(static_cast<int>(httpStatus));
    // Itera sobre todos os servidores configurados
    for (const auto& server : _servers) {
        // Procura o código de status HTTP nas páginas de erro configuradas para o servidor atual
        auto it = server.errorPages.find(statusCode);
        // Se encontrar uma correspondência, retorna o caminho da página de erro personalizada
        if (it != server.errorPages.end()) {
            
            return it->second;
        }
    }
    // Se nenhuma correspondência for encontrada, retorna uma string vazia
    return "";
}