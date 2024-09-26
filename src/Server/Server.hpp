#ifndef SERVER_HPP
# define SERVER_HPP

# include <exception>

namespace Server {
	void    configServer();
	void	startServer();

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
};

#endif //SERVER_HPP