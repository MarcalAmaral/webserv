#ifndef SERVER_HPP
# define SERVER_HPP

# include <netinet/in.h>
# include <exception>

class Server {
	private:
		struct sockaddr_in _serverAddr;
		int	_epollFd;
		int	_serverSocket;
	public:
		Server();
		~Server();

		class ServerBindSocketException : public std::exception {
			public:
				const char *what() const throw();
		};

		class ServerCreateSocketException : public std::exception {
			public:
				const char *what() const throw();
		};

		class ServerSetSocketOptionsException : public std::exception {
			public:
				const char *what() const throw();
		};

		class ServerListenException : public std::exception {
			public:
				const char *what() const throw();
		};

		class ServerEPollCreateInstanceException : public std::exception {
			public:
				const char *what() const throw();
		};

		class ServerEPollAddFdException : public std::exception {
			public:
				const char *what() const throw();
		};

		void	initLoopEvent(void);
};

#endif //SERVER_HPP