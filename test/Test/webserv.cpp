#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <sstream>

#define RESPONSE "\
HTTP/1.1 200 OK\r\ncontent-type: text/html; charset=utf-8\r\ncontent-length:56\r\nConnection: Keep-Alive\r\nKeep-Alive: timeout=5, max=1000\r\n\r\nHello world\n<img src='resize_chicken.png' alt='chicken'>"

using namespace std;

int	main(void) {
	int socketFd;
	sockaddr_in serverAddress;
	std::string http("HTTP/1.1 200 OK\r\n");
	std::string	content("Content-Type: text/html; charset=UTF-8\r\n\r\n");
 	std::string corpo("<!DOCTYPE html>\n<html lang='pt'>\n<head>\n<meta charset='UTF-8'>\n<title>Exemplo</title>\n</head>\n<body><img src='./resize_chicken.png' alt='franguinho'>\n<h1>Conteúdo HTML</h1>\n</body>\n</html>");
	std::string	content2("Content-Length: 197\r\n\r\n");





 	//std::string image2("--boundary-string\nContent-Type: image/png\r\nContent-Disposition: inline; filename='imagem.jpg'\r\nContent-Length: 3767\r\n\r\n");
 

	ifstream file("resize_chicken.png");
	std::stringstream b;
	b << file.rdbuf();

	string seila = b.str();
	string image("HTTP/1.1 200 OK\r\ncontent-type: image/apng; charset=utf-8\r\ncontent-length:3767\r\nConnection: Keep-Alive\r\nKeep-Alive: timeout=5, max=1000\r\n\r\n");
	http += content;
	http += content2;
	http += corpo;

	image += seila;

	socketFd = socket(AF_INET, SOCK_STREAM, 0);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	bind(socketFd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	listen(socketFd, 5);
	int clientSocket = accept(socketFd, nullptr, nullptr);
	char buffer[2048] = {0};
	recv(clientSocket, buffer, sizeof(buffer), 0);
	cout << buffer << endl;
	send(clientSocket, http.c_str(), http.length(), 0);
	recv(clientSocket, buffer, sizeof(buffer), 0);
	cout << buffer << endl;
	send(clientSocket, image.c_str(), image.length(), 0);
	close(socketFd);
	close(clientSocket);
	return (0);
}