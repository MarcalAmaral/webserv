#ifndef PARSER_HPP
# define PARSER_HPP

# include <sstream>
# include <fstream>
# include <vector>
# define WEBSERV_CONF_FILE_ERROR(file, error) (std::ostringstream() << "webserv: configuration file error: " << file << " " << error).c_str()

namespace Master {
	namespace Parser {
		typedef struct s_conf_file {
			int			currentLine;
			const char *pathname;
			std::vector<std::string> tokens;
			std::vector<int> tokensLine;
			std::ifstream file;
		} t_conf_file;

		void	parser(const char *pathname);
		void	readTokens(t_conf_file *cf);
		void	lineToTokens(t_conf_file *cf, std::string &line);
		void	processTokens(t_conf_file *cf);
		// main directive
		void	handleServer();
		// server directives
		void	handleListen();
		void	handleServerName();
		void	handleErrorPage();
		void	handleClientMaxBodySize();
		// location directives
		void	handleLocation();
		void	handleLocationAllowMethods();
		void	handleLocationRedirect();
		void	handleLocationRoot();
		void	handleLocationAutoIndex();
		void	handleLocationCGI();
		void	handleLocationUploadDir();

		// void	handleServerBlockDirective(std::vector<string> &lines, std::vector<estring>::iterator &start);
	}
}

#endif // PARSER_HPP