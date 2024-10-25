#ifndef MANAGER_HPP
# define MANAGER_HPP

# include <vector>
# include <map>

class Server;

namespace webserv {
	std::vector<Server> _servers;
	// class Manager {
	// 	public:
	// 		Manager();
	// 		~Manager();

	// 	private:
	// };

	namespace parser {
		typedef struct s_conf_file {
			const char *filename;
			std::ifstream file;
		} t_conf_file;

		// void	init_conf_file(t_conf_file *cf);
		void	parser(t_conf_file *cf, char *filename);
		inline namespace validation {
			void	validate_file(t_conf_file *cf);
		}
		inline namespace utils {
			std::string remove_comments_and_spaces(const std::string &line);
		}
	}
}


#endif //MANAGER_HPP