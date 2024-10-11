#ifndef MASTER_CLASS_HPP
# define MASTER_CLASS_HPP

# include <vector>

class Server;
class Client;

namespace Master {
	class MasterClass {
		private:
			std::vector<Server>	_servers;
			std::vector<Client>	_clients;
			int					_epollFd;
		public:
			Master();
			~Master();

			friend class Server;
	};
};

#endif // MASTER_CLASS_HPP