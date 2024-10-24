#ifndef MANAGER_HPP
# define MANAGER_HPP

# include <vector>

class Server;
class Client;

namespace Master {
	class Manager {
		public:
			Manager();
			~Manager();
			void	appendServer(const Server &newServer) {
				_servers.push_back(newServer);
			};

			friend class Server;
		private:
			std::vector<Server>	_servers;
			std::vector<Client>	_clients;
			int					_epollFd;
	};
	Manager manager;
};

#endif // MANAGER_HPP