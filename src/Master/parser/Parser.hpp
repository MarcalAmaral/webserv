#ifndef PARSER_HPP
# define PARSER_HPP

# include <sstream>
# include <fstream>
# include <vector>
# define WEBSERV_CONF_FILE_ERROR(file, error) (std::ostringstream() << "webserv: configuration file error: " << file << " " << error).c_str()

namespace Master {
	namespace Parser {
		typedef struct s_conf_file {
			const char *pathname;
			std::vector<std::string> tokens;
			std::ifstream file;
		} t_conf_file;

		void	parser(const char *pathname);
		void	readTokens(t_conf_file *conf);
		void	lineToTokens(t_conf_file *conf, std::string line);
		// void	handleServerBlockDirective(std::vector<string> &lines, std::vector<estring>::iterator &start);
	}
}

#endif // PARSER_HPP