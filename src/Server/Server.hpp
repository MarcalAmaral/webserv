#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <netinet/in.h>
# include <exception>
# include "defines.hpp"
# include <sys/epoll.h>

class Server : public Request, public Response  {
	private:
		struct sockaddr_in _serverAddr;
		int	_serverSocket;
		int	_eventsOcurred;
		struct epoll_event _events[MAX_EVENTS];
	public:
		Server();
		~Server();

		// class ServerBindSocketException : public std::exception {
		// 	public:
		// 		const char *what() const throw();
		// };

		// class ServerCreateSocketException : public std::exception {
		// 	public:
		// 		const char *what() const throw();
		// };

		// class ServerSetSocketOptionsException : public std::exception {
		// 	public:
		// 		const char *what() const throw();
		// };

		// class ServerListenException : public std::exception {
		// 	public:
		// 		const char *what() const throw();
		// };

		// class ServerEPollCreateInstanceException : public std::exception {
		// 	public:
		// 		const char *what() const throw();
		// };

		// class ServerEPollAddFdException : public std::exception {
		// 	public:
		// 		const char *what() const throw();
		// };

		// void	initLoopEvent(void);
		// void	acceptConnection();
		// void	readRequest(int fd);
		// void	sendResponse(int fd);
		// void	closeConnection(int fd);
		// void	parserConfig(const std::string &pathname);
		void	initServer();
};

#endif //SERVER_HPP