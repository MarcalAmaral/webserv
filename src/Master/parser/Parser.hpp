#ifndef PARSER_HPP
# define PARSER_HPP

# include <sstream>
# include <fstream>
# include <vector>
# include <map>
# include "ParserHandlers.hpp"
# define WEBSERV_CONF_FILE_ERROR(file, error) (std::ostringstream() << "webserv: configuration file error: " << file << " " << error).c_str()

namespace Master {
	namespace Parser {
		#define MAIN_CONF   0x02000000
		#define SRV_CONF    0x04000000
		#define LOC_CONF    0x08000000
		#define CONF_NOARGS      0x00000001
		#define CONF_TAKE1       0x00000002
		#define CONF_TAKE2       0x00000004
		#define CONF_TAKE3       0x00000008
		#define CONF_TAKE4       0x00000010
		#define CONF_TAKE5       0x00000020
		#define CONF_TAKE6       0x00000040
		#define CONF_TAKE7       0x00000080

		#define CONF_MAX_ARGS    8

		#define CONF_TAKE12      (CONF_TAKE1|CONF_TAKE2)
		#define CONF_TAKE13      (CONF_TAKE1|CONF_TAKE3)

		#define CONF_TAKE23      (CONF_TAKE2|CONF_TAKE3)

		#define CONF_TAKE123     (CONF_TAKE1|CONF_TAKE2|CONF_TAKE3)
		#define CONF_TAKE1234    (CONF_TAKE1|CONF_TAKE2|CONF_TAKE3   \
										|CONF_TAKE4)

		#define CONF_ARGS_NUMBER 0x000000ff
		#define CONF_BLOCK       0x00000100
		#define CONF_FLAG        0x00000200
		#define CONF_ANY         0x00000400
		#define CONF_1MORE       0x00000800
		#define CONF_2MORE       0x00001000

		#define MAIN_CONF        0x01000000
		#define ANY_CONF         0xFF000000

		#define CONF_BLOCK_START 1
		#define CONF_BLOCK_DONE  2
		#define CONF_FILE_DONE   3

		#define CORE_MODULE      0x45524F43  /* "CORE" */
		#define CONF_MODULE      0x464E4F43  /* "CONF" */

		#define SERVER_CONF() std::make_pair("server", WS_HTTP_SRV_CONF|WS_CONF_BLOCK|WS_CONF_NOARGS)
		#define
		enum e_context {
			ALL,
			HTTP,
			SERVER,
			LOCATION
		};

		// class Directive {
		// 	private:
		// 		enum e_context _type; 
		// 		std::vector<std::string> _elts;
		// 	public:
		// 		Directive(std::vector<std::string>::iterator &f, std::vector<std::string>::iterator &l, enum e_context type);
		// 		~Directive();
		// };

		typedef struct s_conf_file {
			int			currentLine;
			const char *pathname;
			// std::vector<Directive> directives;
			std::map<string, Handler::HandlerClass *> handlers;
			std::vector<std::string> tokens;
			std::vector<int> tokensLine;
			std::ifstream file;
		} t_conf_file;
	
		typedef struct s_conf_commands {
			std::string cmd;
			unsigned int type;
			void *(*conf_cmd)(t_conf_file *cf, std::vector<string>::iterator &it);
		} t_conf_commands;

		void	parser(const char *pathname);
		void	readTokens(t_conf_file *cf);
		void	appendToken(t_conf_file *cf, const std::string &token);
		void	lineToTokens(t_conf_file *cf, std::string &line);
		void	delimitingDirectives(t_conf_file *cf);
		bool	checkDirectives(std::string &directive, enum e_context type);
		void	processTokens(t_conf_file *cf);

		// main directive
		void	handleServer(t_conf_file *cf, std::vector<std::string>::iterator &it, std::vector<int>::iterator &curLine);

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