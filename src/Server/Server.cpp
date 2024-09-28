#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include "Server.hpp"
#include <aio.h>

Server::Server(void) {
	int	optval = 1;
	struct epoll_event ev;
	_epollFd = epoll_create1(0);
	if (_epollFd == -1)
		throw (ServerEPollCreateInstanceException());
	_serverSocket = socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK, TCP_PROTOCOL);
	if (_serverSocket == -1) {
		close(_epollFd);
		throw (ServerCreateSocketException());
	}
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
		close(_epollFd);
		close(_serverSocket);
		throw (ServerSetSocketOptionsException());
	}
	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_port = htons(1027);
	_serverAddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(_serverSocket, (struct sockaddr *)&_serverAddr, sizeof(serverAddr)) == -1) {
		close(_epollFd);
		close(_serverSocket);
		throw (ServerBindSocketException());
	}
	if (listen(_serverSocket, 5) == -1) {
		close(_epollFd);
		close(_serverSocket);
		throw (ServerListenException());
	}
	ev.data.fd = _serverSocket;
	ev.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, _serverSocket, &ev) == -1) {
		close(_epollFd);
		close(_serverSocket);
		throw (ServerEPollAddFdException());
	}
}

Server::~Server(void) {}

void	Server::initLoopEvent(void) {
	while (true) {
		epoll_wait
	}
}

// int	Server::initServer(void) {
// 	struct sockaddr_in serverAddr;
// 	int		serverSocket;
// 	int		epollFd;
// 	struct epoll_event ev;


// 	if ((serverSocket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) == -1)
// 		throw (ServerCreateSocketException());
// 	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (void *)1, sizeof(int)) == -1)
// 		throw (ServerSetSocketOptionsException());
// 	serverAddr.sin_family = PF_INET;
// 	serverAddr.sin_port = htons(1027);
// 	serverAddr.sin_addr.s_addr = INADDR_ANY;
// 	if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
// 		throw (ServerBindSocketException());
// 	if (listen(serverSocket, 10) == -1)
// 		throw (ServerListenException());
// 	ev.data.fd = socketServer;
// 	if (epoll_ctl(epollFd, EPOLL_CTL_ADD, socketServer, &ev) == -1)
// 		std::cerr << "Error: cannot too add server socket to epoll" << std::endl; 
// 	return (epollFd);
// }
