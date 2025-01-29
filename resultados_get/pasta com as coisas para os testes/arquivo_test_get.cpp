#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#include <sstream>
#include <cerrno>
#include <cstring>






//deu certo para o GET!
int pathIsValid(const char *absolutePath, int defaultValue)
{
	struct stat info;
	std::string errorMessage;

	if (stat(absolutePath, &info) == -1)
	{
		int errorCode = errno;
		errorMessage = strerror(errorCode);
		if (errorMessage == "Not a directory" || errorMessage == "No such file or directory"){
			return 404;
		}
		if (errorMessage == "Permission denied"){
			return 403;
		}
	}

	if (access(absolutePath, F_OK | R_OK) != 0){
		return 403;
	}

	return defaultValue;
}

int pathIsValidGet(const std::string absolutePath, bool canListDirectoryIfPathPointsToADirectory){

	struct stat info;
	std::string errorMessage;

	if (stat(absolutePath.c_str(), &info) == -1)
	{
		int errorCode = errno;
		errorMessage = strerror(errorCode);
		if (errorMessage == "Not a directory" || errorMessage == "No such file or directory"){
			return 404;
		}
		if (errorMessage == "Permission denied"){
			return 403;
		}
	}

	if (access(absolutePath.c_str(), F_OK | R_OK) != 0){
		return 403;
	}

    if (S_ISDIR(info.st_mode)) {
		if (!absolutePath.empty() && absolutePath[absolutePath.size() - 1] != '/'){
			return 301;
		}
		if (!canListDirectoryIfPathPointsToADirectory){
			return 403;
		}
    }
	return 200;
}

int pathIsValidPost(const char *absolutePath){
	struct stat info;
	std::string errorMessage;

	if (stat(absolutePath, &info) == -1)
	{
		int errorCode = errno;
		errorMessage = strerror(errorCode);
		if (errorMessage == "Not a directory" || errorMessage == "No such file or directory"){
			return 404;
		}
		if (errorMessage == "Permission denied"){
			return 403;
		}
	}

	if (access(absolutePath, F_OK | R_OK) != 0){
		return 403;
	}

	return 405;
}

int pathIsValidDelete(const char *absolutePath){
	return 405;
}



int main(int argc, char **argv)
{
	const char *absolutePath = argv[1];
	std::string httpVerb = argv[2];
	bool canListDirectory = (std::string(argv[3]) == std::string("y"));

	int retorno = 0;

	if (httpVerb == "GET"){
		retorno = pathIsValidGet(absolutePath, canListDirectory);
	}else if (httpVerb == "POST"){
		retorno = pathIsValidPost(absolutePath);
	}else if (httpVerb == "DELETE"){
		retorno = pathIsValidDelete(absolutePath);
	}

	std::stringstream ss;
	ss << retorno;
	std::cout << ss.str() << std::endl;

	return 0;
}
