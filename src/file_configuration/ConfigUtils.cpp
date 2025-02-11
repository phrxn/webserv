#include "Define.hpp"
#include "Config.hpp"
#include "../net/http/HTTPMethods.hpp"

namespace ConfigUtils {
    short	getServerCount( const std::string &fileName ) {
        std::ifstream configFile(fileName.c_str());
        if (!configFile.is_open() || configFile.fail()) {
            throw std::runtime_error(ERROR_OPEN_CONFIG_FILE);
        }

        short serverCount = 0;
        short braceCount = 0;
        std::string line;
        while (std::getline(configFile, line)) {
            if (line.find("server_name") == std::string::npos && 
                line.find("server") != std::string::npos) {
                serverCount++;
            } 
            if (line.find("{") != std::string::npos || 
                line.find("}") != std::string::npos) {
                braceCount++;
            }
            if (line.find("{") != std::string::npos && 
                line.find("}") != std::string::npos) {
                throw std::runtime_error(ERROR_INVALID_SERVER);
            }
        }
        if (braceCount != serverCount * 2) {
            throw std::runtime_error(ERROR_INVALID_SERVER);
        }
        configFile.close();
        return (serverCount);
    }


	std::string	trim( const std::string &serverBlock ) {
        std::stringstream	timmedServerBlock;
        std::istringstream	serverStream(serverBlock);
        std::string	line;

        while (std::getline(serverStream, line)) {
            size_t first = line.find_first_not_of(' ');
            if (first == std::string::npos) {
                continue;
            }
            size_t last = line.find_last_not_of(' ');
            line = line.substr(first, (last - first + 1));

            if (line.empty()) { continue; }

            if ((line.find("server") != std::string::npos &&
                line.find("server_name") == std::string::npos) ||
                line.find("{") != std::string::npos ||
                line.find("}") != std::string::npos) {
                continue;
            }

            size_t firstNonSpacePos = line.find_first_not_of(" \t");
            if (firstNonSpacePos != std::string::npos) {
                line = line.substr(firstNonSpacePos);
            }

            if (line.find("#") != std::string::npos) {
                if (line[0] == '#') {
                    continue;
                } else {
                    line = line.substr(0, line.find("#"));
                }
            }
            timmedServerBlock << line << std::string("\n");
        }
        return (timmedServerBlock.str());
    }

    bool	isRepeatedMethod( std::vector<HTTPMethods::Method> &methodsVector, 
        HTTPMethods::Method method ) {
        if (std::find(methodsVector.begin(), methodsVector.end(), method) 
            != methodsVector.end()) {
            return true;
        } else { return false; }
    }

	bool	directoryExists( const std::string &path ) {
        struct stat info;
        if (stat(path.c_str(), &info) != 0 || !(info.st_mode & S_IFDIR)) {
            return false;
        } else { return true; }
    }

    bool	fileExists( const std::string &path ) {
        struct stat info;
        if (stat(path.c_str(), &info) != 0 || !(info.st_mode & S_IFREG)) {
            return false;
        } else { return true; }
    }

    void	formatPath( std::string &path ) {
        if (path[0] == '/') {
            if (!ConfigUtils::directoryExists(path)) { 
                path = "." + path;
            }
        } else if (path[0] != '.' && path[1] != '/') {
            path = "./" + path;
        }
    }

    void	validateFullLocationPath( RouteConfig &location ) {
        if (location.cgiEnabled) { return ; }
        if (location.redirectSet ) { return ; }

        std::string effectiveRoot;
        if (location.rootSet) { 
            effectiveRoot = location.rootDir; 
        } else { effectiveRoot = DEFAULT_ROOT; }
        
        std::string fullPath = effectiveRoot + location.locationPath;
        if (!ConfigUtils::directoryExists(fullPath)) {
            throw std::runtime_error(ERROR_INVALID_LOCATION_PATH);
        }
    }

    void	validateFullCGIPath( RouteConfig &location ) {
        if (!location.cgiEnabled) { return ; }

        std::string cgiPath = location.cgiPath;
        size_t	lastDot = cgiPath.find_last_of('.');
        if (cgiPath.substr(lastDot) != location.cgiExtension) {
            throw std::runtime_error(ERROR_INVALID_CGI_EXTENSION);
        }

        std::string effectiveRoot;
        if (location.rootSet) { 
            effectiveRoot = location.rootDir; 
        } else { effectiveRoot = DEFAULT_ROOT; }

        std::string fullPath = effectiveRoot + "/" + cgiPath;
        if (!ConfigUtils::fileExists(fullPath)) {
            throw std::runtime_error(ERROR_INVALID_CGI_PATH);
        }
    }

 	void	printServerStruct( const ServerConfig &server ) {
		std::cout << "              Server Configs " << std::endl;
		std::cout << "=========================================" << std::endl;
		std::cout << "port: " << server.port << std::endl;
		std::cout << "host: " << server.host << std::endl;
		std::cout << "server_name: " << server.serverName << std::endl;
		std::cout << "limit_body_size: " << server.limitBodySize << std::endl;
		for (errorMap::const_iterator it = server.errorPages.begin(); 
			it != server.errorPages.end(); ++it) {
			std::cout << "error_pages: " << it->first << " " << it->second << std::endl;
		}
		std::cout << "[ Server Locations ]: " << std::endl;
		for (std::vector<RouteConfig>::const_iterator it = server.routes.begin(); 
			it != server.routes.end(); ++it) {
			std::cout << "\tHTTP Method: ";
			for (std::vector<HTTPMethods::Method>::const_iterator it2 = it->methods.begin(); 
				it2 != it->methods.end(); ++it2) {
				if (*it2 == HTTPMethods::GET) {
					std::cout << "GET";
				} else if (*it2 == HTTPMethods::POST) {
					std::cout << "POST";
				} else if (*it2 == HTTPMethods::DELETE) {
					std::cout << "DELETE";
				}
				std::cout << " ";
			}
			std::cout << std::endl;
			std::cout << "\tlocation_path: " << it->locationPath << std::endl;
			std::cout << "\troot: " << it->rootDir << std::endl;
			std::cout << "\tindex: " << it->indexFile << std::endl;
			std::cout << "\tredirect: " << it->redirect << std::endl;
			std::cout << "\tupload_path: " << it->uploadPath << std::endl;
			std::cout << "\tautoindex: " << it->autoindex << std::endl;
			std::cout << "\tupload_enabled: " << it->uploadEnabled << std::endl;
			std::cout << "\troot_set: " << it->rootSet << std::endl;
			std::cout << "\tredirect_set: " << it->redirectSet << std::endl;
			std::cout << "\tCGI path: " << it->cgiPath << std::endl;
			std::cout << "\tCGI extension: " << it->cgiExtension << std::endl;
			std::cout << "\tCGI enabled: " << it->cgiEnabled << std::endl;
			std::cout << std::endl;
		}
	}

}
