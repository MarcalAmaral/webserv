#include <signal.h>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include "Server.class.hpp"

#define HTTP_RESPONSE "HTTP/1.1 200 OK\r\nContent-Lenght: HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length:13\r\n\r\nHello world\n"

Server::Server(void) {
	int	optval = 1;
	struct epoll_event ev;
	_epollFd = epoll_create1(0);
	if (_epollFd == -1)
		throw (ServerEPollCreateInstanceException());
	_serverSocket = socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (_serverSocket == -1) {
		close(_epollFd);
		throw (ServerCreateSocketException());
	}
	if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
		close(_epollFd);
		close(_serverSocket);
		throw (ServerSetSocketOptionsException());
	}
	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_port = htons(1027);
	_serverAddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(_serverSocket, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr)) == -1) {
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
	ev.events = EPOLLIN;
	if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, _serverSocket, &ev) == -1) {
		close(_epollFd);
		close(_serverSocket);
		throw (ServerEPollAddFdException());
	}
}

Server::~Server(void) {}

// void	*threadRoutine(void *arg) {

// }

// void	Server::initThreads(void) {

// }

void	Server::acceptConnection() {
	int	clientFd;
	int	socketFlags;
	socklen_t addrlen;
	struct epoll_event ev;
	struct sockaddr_in clientAddr;

	memset(&clientAddr, 0, sizeof(clientAddr));
	memset(&ev, 0, sizeof(ev));
	addrlen = sizeof(clientAddr);
	clientFd = accept(_serverSocket, (struct sockaddr *)&clientAddr, &addrlen);
	if (clientFd == -1) {
		std::cerr << "Error: cannot accept new connection" << std::endl;
		return ;
	}
	memset(&ev, 0, sizeof(ev));
	ev.data.fd = clientFd;
	ev.events = EPOLLIN | EPOLLRDHUP;
	socketFlags = fcntl(ev.data.fd, F_GETFL);
	if ((socketFlags = fcntl(ev.data.fd, F_SETFL, socketFlags | O_NONBLOCK)) == -1) {
		std::cerr << "Error: cannot set new flags to client socket" << std::endl;
		close(ev.data.fd);
		return ;
	}
	if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, ev.data.fd, &ev) == -1) {
		std::cerr << "Error: Cannot add new socket fd to epoll" << std::endl;
		return ;
	}
	std::cout << "New connection established on address: " << clientAddr.sin_addr.s_addr
	<< " on port: " << clientAddr.sin_port << " on fd: " << clientFd << std::endl;
}

void	Server::readRequest(int fd) {
	char	buffer[BUFFER_SIZE + 1];
	int		bytesRead = 0;
	struct epoll_event ev;
	std::string request("");

	memset(&ev, 0, sizeof(ev));
	memset(buffer, 0, sizeof(buffer));
	while ((bytesRead = recv(fd, buffer, BUFFER_SIZE, 0)) && bytesRead != -1) {
		request += buffer;
		std::cout << request << std::endl;
		memset(buffer, 0, sizeof(buffer));
	}
	if (request.find("\r\n\r\n") != 0) {
		ev.data.fd = fd;
		ev.events = EPOLLOUT | EPOLLRDHUP;
		epoll_ctl(_epollFd, EPOLL_CTL_MOD, fd, &ev);
	}
	// std::cout << "Content received from fd: " << ev.data.fd << " \n" + request << std::endl;
}

void	Server::sendResponse(int fd) {
	if (send(fd, HTTP_RESPONSE, strlen(HTTP_RESPONSE), 0) == -1) {
		closeConnection(fd);
		std::cerr << "Error: to send response to fd: " << fd << std::endl; 
	}
	else
		std::cout << "Response sended to fd: " << fd << std::endl;
	closeConnection(fd);
	
}

void	Server::closeConnection(int fd) {
	std::cout << "connection closed on fd: " << fd << std::endl;
	epoll_ctl(_epollFd, EPOLL_CTL_DEL, fd, NULL);
	close(fd);
}

void	Server::initLoopEvent(void) {
	signal(SIGPIPE, SIG_IGN);
	while (true) {
		_eventsOcurred = epoll_wait(_epollFd, _events, MAX_EVENTS, -1);
		if (_eventsOcurred == -1)
			std::cerr << "Error: epoll_wait" << std::endl;
		if (_eventsOcurred > 0) {
			for (int i = 0; i < _eventsOcurred; ++i) {
				if (_events[i].events & EPOLLIN && _events[i].data.fd == _serverSocket)
					acceptConnection();
				else if (_events[i].events & EPOLLIN) 
					readRequest(_events[i].data.fd);
				else if (_events[i].events & EPOLLOUT)
					sendResponse(_events[i].data.fd);
				else if (_events[i].events & EPOLLRDHUP || _events[i].events & EPOLLHUP) {
					closeConnection(_events[i].data.fd);
					continue ;
				}
			}
		}
	}
}
