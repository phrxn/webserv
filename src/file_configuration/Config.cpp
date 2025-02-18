
#include "Config.hpp"
#include "Define.hpp"
#include <sstream>



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
				server.addRoute(location);
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

        if (tokens[0] == "methods"){
            RouteExtraction::extractMethods(tokens, location);
        }else if (tokens[0] == "location_path"){
            RouteExtraction::extractLocationPath(tokens, location);
		}else if (tokens[0] == "root"){
            RouteExtraction::extractRootDir(tokens, location);
        }else if (tokens[0] == "index"){
            RouteExtraction::extractIndexFile(tokens, location);
        }else if (tokens[0] == "redirect"){
            RouteExtraction::extractRedirect(tokens, location);
        }else if (tokens[0] == "autoindex"){
            RouteExtraction::extractAutoindex(tokens, location);
        }else if (tokens[0] == "upload_path"){
            RouteExtraction::extractUploadPath(tokens, location);
        }else if (tokens[0] == "upload_enabled"){
            RouteExtraction::extractUploadEnabled(tokens, location);
        }else if (tokens[0] == "cgi_path"){
            RouteExtraction::extractCGIPath(tokens, location);
		}else if (tokens[0] == "cgi_enable"){
            RouteExtraction::extractCGIEnable(tokens, location);
        }else{
            throw std::runtime_error("ERROR_INVALID_KEY");
        }
    }
}

// Método público para obter os servidores
std::vector<ServerConfig> Config::getServers(void) const
{
    return this->_servers;
}