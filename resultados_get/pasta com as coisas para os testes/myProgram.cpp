#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#include <sstream>
#include <cerrno>
#include <cstring>

int isAndDirectory(const char *arquivo, bool podeListarDiretorios){

    struct stat info;
    std::string errorMessage;
	int retorno = -1;

    if (stat(arquivo, &info) == -1) {
	int errorCode = errno;
	errorMessage = strerror(errorCode);
	//std::cout << "stat: " << errorMessage << std::endl;
	if (errorMessage == "Not a directory" || errorMessage == "No such file or directory")
	   retorno = 404;
	if (errorMessage == "Permission denied")
	   retorno = 403;
    }

	if (podeListarDiretorios && retorno == 403){
		retorno = 404;
	}

	if (retorno != -1){
		return retorno;
	}

    if (S_ISDIR(info.st_mode)) {
	    return 1;
    } else if (S_ISREG(info.st_mode)) {
	    return 0;
    } else {
        printf("O caminho não é nem um diretório, nem um arquivo regular.\n");
    }
    return -1;
}

int main(int argc, char **argv) {
    const char *arquivo = argv[1];
	bool isToListDirectories = (std::string(argv[2]) == std::string("y"));

    int retorno = isAndDirectory(arquivo, isToListDirectories);
    if (retorno > 2){
       std::stringstream ss;
       ss << retorno;
       std::cout << ss.str() << std::endl;
       return -1;
    }

	if (access(arquivo, F_OK | R_OK) != 0) {
		std::cout << "403" << std::endl;
		return -1;
	}

	std::cout << "200" << std::endl;

    return 0;

/*
    struct stat info;

    if (stat(arquivo, &info) == -1) {
        perror("stat");
	printf("404\n");
	return 1;
    }

    if (S_ISDIR(info.st_mode)) {
        printf("O caminho é um diretório.\n");
    } else if (S_ISREG(info.st_mode)) {
        printf("O caminho é um arquivo regular.\n");
    } else {
        printf("O caminho não é nem um diretório, nem um arquivo regular.\n");
    }

    // Tenta acessar o arquivo com a permissão de leitura
    if (access(arquivo, F_OK | R_OK) == 0) {
        printf("O arquivo '%s' existe.\n", arquivo);
    } else {
	perror("");
    }


    // Tenta mudar o diretório
    if (chdir(arquivo) == -1) {
        // Se ocorrer um erro, imprime uma mensagem de erro
        perror("Erro ao mudar o diretório");
        return 1;
    }
*/

}
