#ifndef MANAGER_HPP
# define MANAGER_HPP

# include <vector>

class Server;
class Client;

namespace Master {
	class Manager {
		private:
			std::vector<Server>	_servers;
			std::vector<Client>	_clients;
			int					_epollFd;
		public:
			Manager();
			~Manager();

			friend class Server;
	};
};

#endif // MANAGER_HPP