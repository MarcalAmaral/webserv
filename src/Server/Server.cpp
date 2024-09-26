#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include "Server.hpp"

void Server::configServer(int epollFd) {
	struct sockaddr_in serverAddr;
	int		serverSocket;
	struct epoll_event ev;

	if ((serverSocket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) == -1)
		throw (ServerCreateSocketException());
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (void *)1, sizeof(int)) == -1)
		throw (ServerSetSocketOptionsException());
	serverAddr.sin_family = PF_INET;
	serverAddr.sin_port = htons(1027);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
		throw (ServerBindSocketException());
	if (listen(serverSocket, 10) == -1)
		throw (ServerListenException());
	ev.data.fd = socketServer;
	if (epoll_ctl(epollFd, EPOLL_CTL_ADD, socketServer, &ev) == -1)
		std::cerr << "Error: cannot too add server socket to epoll" << std::endl; 
}

void Server::startServer() {
	int	epollFd;

	if ((epollFd = epoll_create1(0)) == -1)
		throw (EPollCreateInstanceException());
	if (epoll_ctl(epollFd, ))

}