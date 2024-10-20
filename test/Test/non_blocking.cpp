#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <unistd.h>

#define BUFFER_SIZE 4096
#define MAX_EVENTS 10

int	main(void) {
	char	msg[BUFFER_SIZE] = "Hello world\n";
	int		bytesRead;
	char buffer[BUFFER_SIZE + 1] = {0};
	struct sockaddr_in serverAddr;
	struct epoll_event ev, evArray[MAX_EVENTS];
	int	epollWaitRet = 0;
	int epollFd;
	int nonBlockingFd;
	int	serverSocket;
	int	clientSocket = 0;
	int temp = 1;

	if ((epollFd = epoll_create1(0)) == -1)
		return (printf("Error: create epoll instance\n"), EXIT_FAILURE);
	if ((serverSocket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) == -1)
		return (close(epollFd), printf("Error: create socket\n"), EXIT_FAILURE);
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(temp)) == -1)
		return (1);
	serverAddr.sin_family = PF_INET;
	serverAddr.sin_port = htons(1027);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
		return (close(epollFd), close(serverSocket), printf("Error: bind socket\n"), EXIT_FAILURE);
	if (listen(serverSocket, 10) == -1)
		return (close(epollFd), close(serverSocket), printf("Error: listen socket\n"), EXIT_FAILURE);
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = serverSocket;
	if (epoll_ctl(epollFd, EPOLL_CTL_ADD, serverSocket, &ev) == -1)
		return (close(epollFd), close(serverSocket), printf("Error: add server socket to epoll\n"));
	while (true) {
		if ((epollWaitRet = epoll_wait(epollFd, evArray, MAX_EVENTS, -1)) == -1)
			printf("Error: epoll_wait %s\n", strerror(errno));
		if (epollWaitRet > 0) {
			for (int i = 0; i < epollWaitRet; ++i) {
				if (evArray[i].events & EPOLLIN && evArray[i].data.fd == serverSocket) {
					clientSocket = accept(serverSocket, NULL, NULL);
					memset(&ev, 0, sizeof(ev));
					ev.data.fd = clientSocket;
					ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
					if (epoll_ctl(epollFd, EPOLL_CTL_ADD, clientSocket, &ev) == -1)
						return (printf("Error: add client socket to epoll\n"), EXIT_FAILURE);
					printf("Accept new connection\n");
				}
				else {
					if (evArray[i].events & EPOLLIN) {
						if ((bytesRead = recv(evArray[i].data.fd, buffer, BUFFER_SIZE, 0)) != 0) {
							buffer[bytesRead] = '\0';
							printf("received from fd %d\n%s", evArray[i].data.fd, buffer);
							memset(buffer, 0, BUFFER_SIZE);
							memset(&ev, 0, sizeof(ev));
							ev.data.fd = evArray[i].data.fd;
							epoll_ctl(epollFd, EPOLL_CTL_DEL, ev.data.fd, &ev);
							close(ev.data.fd);
						}
					}
					if (evArray[i].events & EPOLLOUT) {
						send(evArray[i].data.fd, msg, strlen("Hello world\n"), 0);
						// memset(buffer, 0, BUFFER_SIZE);
						// memset(&ev, 0, sizeof(ev));
						// ev.data.fd = evArray[i].data.fd;
						// epoll_ctl(epollFd, EPOLL_CTL_DEL, ev.data.fd, &ev);
						// close(ev.data.fd);
					}
				}
			}
			memset(evArray, 0, sizeof(evArray));
		}
	}
}