#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#include <sstream>
#include <cerrno>
#include <cstring>


//deu certo para o GET!
int pathIsValid(const char *absolutePath)
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

	return 200;
}

int main(int argc, char **argv)
{
	const char *absolutePath = argv[1];

	int retorno = pathIsValid(absolutePath);

	std::stringstream ss;
	ss << retorno;
	std::cout << ss.str() << std::endl;

	return 0;
}
