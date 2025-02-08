#include "../../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../../libs/googletest/googletest/include/gtest/gtest.h"

#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>

#include <string>

#include "ArrayChar.hpp"
#include "CGIEnvironmentVariables.hpp"
#include "ChildExecuteProcessCGI.hpp"
#include "FilesToCGI.hpp"

#include <fstream>

int createFakeFDToTest(std::string pos){

    const char *shm_name = "/shared_mem_example";

	std::string name = shm_name + pos;

    size_t length = 0;

    // Criação e mapeamento do arquivo de memória compartilhada
    int fd = shm_open(name.c_str(), O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("Erro ao criar/shm_open");
        return -1;
    }

    if (ftruncate(fd, length) == -1) {
        perror("Erro ao ajustar o tamanho do arquivo compartilhado");
        close(fd);
        return -1;
    }

    return fd;
}

class SystemCallsMockToChildProcess : public SystemCalls{

public:

	error::StatusOr<int> execve(const char *pathname, char *const argv[], char *const envp[]) const{
        (void)pathname;
		(void)argv;
		(void)envp;

		ArrayChar arrayChar;
		if (argv){
			char ** argvToFree = const_cast<char **>(argv);
			arrayChar.freePointerToArray(argvToFree);
		}
		if (envp){
			char ** envpToFree = const_cast<char **>(envp);
			arrayChar.freePointerToArray(envpToFree);
		}

		char buffer_in[20];
		// char buffer_out[20];
		// char buffer_err[20];
		memset(buffer_in, 0, 20);
		// memset(buffer_out, 0, 20);
		// memset(buffer_err, 0, 20);

		int readed_in = ::read(0, buffer_in, 20);

		std::string enter(buffer_in);

		if (readed_in != 9){
			exit(1);
		}

		if (enter != "my input!"){
			exit(2);
		}

		int writed_out = ::write(1, "my output!", 10);

		if (writed_out != 10){
			exit(3);
		}

		int writed_err = ::write(2, "my stderr!!", 11);
		if (writed_err != 11){
			exit(4);
		}
		SUCCEED();
		exit(0);

	}
};

class HTTPRequestMocktToFileToCGI1 : public HTTPRequest {
	public:
	HTTPRequestMocktToFileToCGI1()
		 : HTTPRequest(NULL, NULL) {}
     MOCK_METHOD(std::string, getBody, (), (const override));
};


TEST(ChildExecuteProcessCGITest, execute_fileDescriptordup2){

	HTTPRequestMocktToFileToCGI1 *httpReq = new HTTPRequestMocktToFileToCGI1;
	EXPECT_CALL(*httpReq, getBody())
		.Times(1)
		.WillOnce(testing::Return("my input!"));

	std::string path = "tests/integration/folder_to_test_ChildExecuteProcessCGI/";

	ArrayChar _arrayChar;
	_arrayChar.addString("/program");
	_arrayChar.addString("/path/to/file");

	CGIEnvironmentVariables _cGIEnvironmentVariables;
    FilesToCGI _filesToCGI;
	_filesToCGI.setDefaultDirectoryToSaveTheFiles(path);

	_filesToCGI.createFileDescriptors(*httpReq);
	delete httpReq;

	pid_t pid = fork();

	if (pid == -1){
		FAIL();
	}
	if (pid == 0){
		ChildExecuteProcessCGI child(_arrayChar, _cGIEnvironmentVariables, _filesToCGI);
		SystemCallsMockToChildProcess *sc = new SystemCallsMockToChildProcess;
		child.setSystemCalls(sc);
		child.execute();
	}else{
		int wstatus;
		wait(&wstatus);
		if (WIFSIGNALED(wstatus)){
			FAIL();
		}
		if (WIFEXITED(wstatus)){
			int returned = WEXITSTATUS(wstatus);
			if (returned != 0){
				FAIL();
			}
		}
	}

    // Ler os dados de saída
	std::ifstream &output = _filesToCGI.getOutputFile();
	std::ifstream &stderr = _filesToCGI.getStderrFile();

	if (!output.is_open()){
		FAIL();
	}
	if (!stderr.is_open()){
		FAIL();
	}

	std::stringstream inputBuffer;
	inputBuffer << output.rdbuf();
	std::stringstream outputBuffer;
	outputBuffer << stderr.rdbuf();


    if (inputBuffer.str() != "my output!") {
        FAIL();
    }

    if (outputBuffer.str() != "my stderr!!") {
        FAIL();
    }

    SUCCEED();
}