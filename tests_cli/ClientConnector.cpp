#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#include <vector>

#include "Menu.hpp"

int main(){

  Menu m;

  m.mainMenu();

}



/*
int main()
{
	pthread_t recv_thread;
	SocketClient socketClient;

	int socket = socketClient.createSocketClient("127.0.0.1", 3000);
	if (socket == -1) return 0;

	ThreadReceiveMessage thread(&recv_thread, socket);
    thread.startThread();

	std::cout << "Conectado ao servidor!" << std::endl;

	// Loop principal para enviar mensagens
	std::string message;
	while (true)
	{
		std::getline(std::cin, message); // Lê uma linha do usuário
		message += "\n";
		if (send(socket, message.c_str(), message.length(), 0) < 0)
		{
			std::cerr << "Erro ao enviar mensagem: " << strerror(errno) << std::endl;
			break;
		}
	}

	// Fecha o socket e espera a thread terminar
	close(socket);

	return 0;
}
*/