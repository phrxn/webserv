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

    bool isRepeatedMethod(const std::vector<HTTPMethods::Method> &methodsVector, HTTPMethods::Method method ) {
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

	bool	pathEndsWithSlash(const std::string &path) {
		if (!path.empty() && path[path.size() - 1] == '/') {
			return true;
		} else { return false; }
	}

 	void	printServerStruct( const ServerConfig &server ) {
		std::cout << "              Server Configs " << std::endl;
		std::cout << "=========================================" << std::endl;
		std::cout << "port: " << server.getPort() << std::endl;
		std::cout << "host: " << server.getHost() << std::endl;
		std::cout << "server_name: " << server.getServerName() << std::endl;
		std::cout << "limit_body_size: " << server.getLimitBodySizeInBytes() << std::endl;

		for (errorMap::const_iterator it = server.getErrorPages().begin();
			it != server.getErrorPages().end(); ++it) {
			std::cout << "error_pages: " << it->first << " " << it->second << std::endl;
		}

		const std::vector<RouteConfig> &routes = server.getRoutes();

		std::cout << "[ Server Locations ]: " << std::endl;
		for (std::vector<RouteConfig>::const_iterator it = routes.begin(); it != routes.end(); ++it) {
			std::cout << "\tHTTP Method: ";
			for (std::vector<HTTPMethods::Method>::const_iterator it2 = it->getMethods().begin();
				it2 != it->getMethods().end(); ++it2) {
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
			std::cout << "\tlocation_path: " << it->getLocationPath() << std::endl;
			std::cout << "\troot: " << it->getRootDir() << std::endl;
			std::cout << "\tindex: " << it->getIndexFile() << std::endl;
			std::cout << "\tredirect: " << it->getRedirect() << std::endl;
			std::cout << "\tupload_path: " << it->getUploadPath() << std::endl;
			std::cout << "\tautoindex: " << it->getAutoindex() << std::endl;
			std::cout << "\tupload_enabled: " << it->getUploadEnabled() << std::endl;
			std::cout << "\troot_set: " << it->getRootSet() << std::endl;
			std::cout << "\tredirect_set: " << it->getRedirectSet() << std::endl;
			std::cout << "\tCGI path: " << it->getCgiPath() << std::endl;
			std::cout << "\tCGI enabled: " << it->getCgiEnabled() << std::endl;
			std::cout << std::endl;
		}
	}
}
