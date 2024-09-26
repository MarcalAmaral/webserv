#include <iostream>
#include "Server/Server.hpp"
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>

int	main(void) {
	try {
		int	epollFd;
		if ((epollFd = epoll_create1(0)) == -1)
			throw (Server::EPollCreateInstanceException());
		Server::configServer(epollFd);
	} catch (const std::exception &exception) {
		std::cerr << exception.what() << std::endl;
		return (1);
	}
	return (0);
}