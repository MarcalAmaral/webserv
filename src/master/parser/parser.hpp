#ifndef PARSER_HPP
# define PARSER_HPP

# include <sstream>
# include <fstream>
# include <vector>
# include <map>
// # include "ParserHandlers.hpp"
// # define WEBSERV_CONF_FILE_ERROR(file, error) (std::ostringstream() << "webserv: configuration file error: " << file << " " << error).c_str()

namespace master {
	namespace parser {
		// #define MAIN_CONF   0x02000000
		// #define SRV_CONF    0x04000000
		// #define LOC_CONF    0x08000000
		// #define CONF_NOARGS      0x00000001
		// #define CONF_TAKE1       0x00000002
		// #define CONF_TAKE2       0x00000004
		// #define CONF_TAKE3       0x00000008
		// #define CONF_TAKE4       0x00000010
		// #define CONF_TAKE5       0x00000020
		// #define CONF_TAKE6       0x00000040
		// #define CONF_TAKE7       0x00000080

		// #define CONF_MAX_ARGS    8

		// #define CONF_TAKE12      (CONF_TAKE1|CONF_TAKE2)
		// #define CONF_TAKE13      (CONF_TAKE1|CONF_TAKE3)

		// #define CONF_TAKE23      (CONF_TAKE2|CONF_TAKE3)

		// #define CONF_TAKE123     (CONF_TAKE1|CONF_TAKE2|CONF_TAKE3)
		// #define CONF_TAKE1234    (CONF_TAKE1|CONF_TAKE2|CONF_TAKE3   \
		// 								|CONF_TAKE4)

		// #define CONF_ARGS_NUMBER 0x000000ff
		// #define CONF_BLOCK       0x00000100
		// #define CONF_FLAG        0x00000200
		// #define CONF_ANY         0x00000400
		// #define CONF_1MORE       0x00000800
		// #define CONF_2MORE       0x00001000

		#define CONF_BLOCK_START	1
		#define CONF_BLOCK_DONE		2
		#define CONF_FILE_DONE		3
		// #define CONF_PARAM			4

		// #define CORE_MODULE      0x45524F43  /* "CORE" */
		// #define CONF_MODULE      0x464E4F43  /* "CONF" */


		// # define MAIN_CONF (1 << 0)
		// # define SRV_CONF (MAIN_CONF << 1)
		// # define LOC_CONF (MAIN_CONF << 2)

		// enum e_state {
		// 	PARAM,
		// 	BLOCK_START,
		// 	BLOCK_DONE
		// };

		// #define SERVER_CONF() std::make_pair("server", WS_HTTP_SRV_CONF|WS_CONF_BLOCK|WS_CONF_NOARGS)

		// enum e_context {
		// 	ALL,
		// 	HTTP,
		// 	SERVER,
		// 	LOCATION
		// };

		// class Directive {
		// 	private:
		// 		enum e_context _type; 
		// 		std::vector<std::string> _elts;
		// 	public:
		// 		Directive(std::vector<std::string>::iterator &f, std::vector<std::string>::iterator &l, enum e_context type);
		// 		~Directive();
		// };

		// typedef struct s_conf_file {
		// 	int			line;
		// 	const char *pathname;
		// 	// std::vector<Directive> directives;
		// 	// std::map<string, Handler::HandlerClass *> handlers;
		// 	std::vector<std::string> args;
		// 	std::vector<int> args_line;
		// 	std::vector<std::string>::iterator it;
		// 	std::vector<std::string> tokens;
		// 	std::vector<int> tokensLine;
		// 	std::map<std::string, HandlerBase *> handlers;
		// 	std::ifstream file;
		// } t_conf_file;
	
		// typedef struct s_conf_commands {
		// 	std::string cmd;
		// 	unsigned int type;
		// 	void *(*conf_cmd)(t_conf_file *cf, std::vector<string>::iterator &it);
		// } t_conf_commands;
		typedef struct s_conf_file {
			const char *pathname;
			std::ifstream file;
		} t_conf_file;

		typedef struct s_conf {
			t_conf_file *conf_file;
			unsigned int cline;
			std::vector<std::string> args;
		} t_conf; 

		void	parser(t_conf *cf, const char *pathname);
		int		conf_read_token(t_conf *cf);
		// void	read_tokens(t_conf_file *cf);
		// void	append_token(t_conf_file *cf, const std::string &token);
		// void	line_to_tokens(t_conf_file *cf, std::string &line);
		// void	delimiting_directives(t_conf_file *cf);
		// bool	check_directives(std::string &directive, enum e_context type);
		// void	process_tokens(t_conf_file *cf);
		// void	get_args(t_conf_file *cf, unsigned int num_tokens);
		// void	handle_directive(t_conf_file *cf);

		// // main directive
		// // void	handle_server(t_conf_file *cf, std::vector<std::string>::iterator &it, std::vector<int>::iterator &curLine);

		// // server directives
		// void	handle_listen();
		// void	handle_server_name();
		// void	handle_error_page();
		// void	handle_client_max_body_size();

		// // location directives
		// void	handle_location();
		// void	handle_location_allow_methods();
		// void	handle_location_redirect();
		// void	handle_location_root();
		// void	handle_location_auto_index();
		// void	handle_location_cgi();
		// void	handle_location_upload_dir();
		// // void	handleServerBlockDirective(std::vector<string> &lines, std::vector<estring>::iterator &start);
		// // initialize values of t_conf_file cf
		void	init_conf(t_conf *cf);
	}
}

#endif // PARSER_HPPv