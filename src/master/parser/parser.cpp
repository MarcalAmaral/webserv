// #include <vector>
// #include <fstream>
// #include <iostream>
// #include <cstring>
// #include <sstream>
// #include <cctype>
// #include "parser.hpp"
// #include "validations.hpp"
// #include "utils.hpp"
// #include "utils/utils.hpp"
// #include "logger/logger.hpp"

// void	master::parser::init_conf(t_conf_file *cf) {
// 	cf->line = 1;
// 	cf->pathname = NULL;
// 	init_handler_modules(cf);
// }

// void	master::parser::parser(t_conf_file *cf, const char *pathname) {
// 	using namespace master::parser;

// 	if (pathname) {
// 		cf->pathname = pathname;
// 		validation::validate_file(cf);
// 		read_tokens(cf);
// 	}
// #if (PRINT_TOKENS != 1)
// 	process_tokens(cf);
// #endif
// }

// void	master::parser::get_args(t_conf_file *cf, unsigned int num_tokens) {
// 	std::stringstream	ss;
// 	std::string			token;
// 	std::string			elts;
// 	int					line;
// 	for (unsigned int it = 0; it < num_tokens; ++it) {
// 		token = *cf->tokens.begin();
// 		line = *cf->tokensLine.begin();
// 		if (token.find(' ') != std::string::npos) {
// 			ss.str(*token);
// 			while (ss >> elts) {
// 				cf->args.push_back(elts);
// 				cf->args_line.push_back(line);
// 				elts.clear();
// 			}
// 		}
// 		else {
// 			cf->args.push_back(*token);
// 			cf->args_line.push_back(line);
// 		}
// 		cf->tokens.erase(cf->tokens.begin());
// 		cf->tokensLine.erase(cf->tokensLine.begin());
// 	}
// }

// void	master::parser::handle_directive(t_conf_file *cf, enum e_state state, unsigned int context) {
// }

// void	master::parser::processTokens(t_conf_file *cf) {

// }

// // void	Master::Parser::processTokens(t_conf_file *cf) {
// // 	using namespace Master::Parser;
// // 	using namespace Logger;
// // 	enum {
// // 		main,
// // 		srv,
// // 		loc
// // 	} context;
// // 	bool	openSrvBlock = false;
// // 	bool	openLocBlock = false;
// // 	std::vector<int>::iterator cline = cf->tokensLine.begin();

// // 	context = main;
// // 	for (std::vector<std::string>::iterator it=cf->tokens.begin(); it != cf->tokens.end(); ++it) {
// // 		if (context == main) {
// // 			if (checkDirectives(*it, ALL)) {
// // 				if (*it == "server") {
// // 					context = srv;
// // 					// cf->handlers[*it]->handler(cf, NULL, NULL);
// // 				}
// // 				else
// // 					throw (std::runtime_error(cfSyntaxErr(cf->pathname, "directive not allow here", *it, *cline)));
// // 			}
// // 			else
// // 				throw (std::runtime_error(cfSyntaxErr(cf->pathname, "unknown directive", *it, *cline)));
// // 		} else if (context = srv) {
// // 			if (*it == "{" && openSrvBlock == false)
// // 				openSrvBlock = true;
// // 			else if (*it == "}" && openSrvBlock == true)
// // 				openSrvBlock = false;
// // 			else if (*it == "{" && openSrvBlock == true)
// // 				throw (std::runtime_error(cfSyntaxErr(cf->pathname, "unexpected", *it, *cline)));
// // 			else if (*it == "}" && openSrvBlock == false)
// // 				throw (std::runtime_error(cfSyntaxErr(cf->pathname, "unexpected", *it, *cline)));
// // 			else if (checkDirectives(*it, ALL)) {
// // 				if (checkDirectives(*it, SERVER)) {
// // 					if (*it == "location")
// // 						context = loc;
// // 					cf->handlers[*it].handler(cf, _servers.end(), NULL);
// // 				}
// // 				else
// // 					throw (std::runtime_error(cfSyntaxErr(cf->pathname, "directive not allow here", *it, *cline)));
// // 			}
// // 			else
// // 				throw (std::runtime_error(cfSyntaxErr(cf->pathname, "unknown directive", *it, *cline)));
// // 		} else if (context = loc) {
// // 			if (*it == "{" && openLocBlock == false)
// // 				openLocBlock = true;
// // 			else if (*it == "}" && openLocBlock == true)
// // 				openLocBlock = false;
// // 			else if (*it == "{" && openLocBlock == true)
// // 				throw (std::runtime_error(cfSyntaxErr(cf->pathname, "unexpected", *it, *cline)));
// // 			else if (*it == "}" && openLocBlock == false)
// // 				throw (std::runtime_error(cfSyntaxErr(cf->pathname, "unexpected", *it, *cline)));
// // 			else if (checkDirectives(*it, ALL)) {
// // 				if (checkDirectives(*it, SERVER))
// // 					cf->handlers[*it].handler(cf, NULL, _servers.end()._locations.end());
// // 				else
// // 					throw (std::runtime_error(cfSyntaxErr(cf->pathname, "directive not allow here", *it, *cline)));
// // 			}
// // 			else
// // 				throw (std::runtime_error(cfSyntaxErr(cf->pathname, "unknown directive", *it, *cline)));
// // 		}
// // 		cline++;
// // 	}
// // }

// bool	master::parser::check_directives(std::string &directive, enum e_context type) {
// 	const std::string directives[13] = {"server", "listen", "server_name",
// 	"client_max_body_size", "error_page", "location", "allow_methods", "redirect", "root",
// 	"autoindex", "index", "cgi", "upload_dir"};

// 	if (type == parser::ALL) {
// 		for (int i = 0; i < 13; ++i) {
// 			if (directive == directives[i])
// 				return true;
// 		}
// 	} else if (type == parser::HTTP) {
// 		for (int i = 0; i < 1; ++i) {
// 			if (directive == directives[i])
// 				return true;
// 		}
// 	} else if (type == parser::SERVER) {
// 		for (int i = 1; i < 6; ++i) {
// 			if (directive == directives[i])
// 				return true;
// 		}
// 	} else if (type == parser::LOCATION) {
// 		for (int i = 7; i < 13; ++i) {
// 			if (directive == directives[i])
// 				return true;
// 		}
// 	}
// 	return false;
// }

// // void	Parser::processTokens(t_conf_file *cf) {
// // 	enum e_context context;
// // 	bool	startServerBlock = false;
// // 	vector<int>::iterator itLine = cf->tokensLine.begin();

// // 	for (vector<string>::iterator it=cf->tokens.begin(); it != cf->tokens.end(); ++it) {
// // 		if (context == HTTP) {
// // 			if (*it == "server")
// // 				context = SERVER;
// // 			else if (checkDirectives(*it, Parser::ALL))
// // 				throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "directive is not allowed here", *itLine)));
// // 			else
// // 				throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "unknown directive", *itLine)));

// // 		} else if (context == SERVER) {
// // 			if (startServerBlock == false && *it == "{")
// // 				startServerBlock = true;
// // 			else if (startServerBlock == true && *it == "{")
// // 				throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "unexpected", *itLine)));
// // 			else if (startServerBlock == true && *it == "}")
// // 				startServerBlock = false;
// // 			else if (startServerBlock == false && *it == "}")
// // 				throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "unexpected", *itLine)));
// // 			else if (checkDirectives(*it, Parser::ALL) == true) {
// // 				if (checkDirectives(*it, Parser::SERVER) == false)
// // 					throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "directive is not allowed here", *itLine)));
// // 				if (*it == "location")
// // 					context = LOCATION;
// // 				// cf->handlers[*it].handler(cf, it, itLine);
// // 			}
// // 			else
// // 				throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "unknown directive", *itLine)));
			
// // 		} else if (context == LOCATION) {
// // 			continue ;
// // 		}
// // 		++itLine;
// // 	}
// // }

// void	master::parser::appendToken(t_conf_file *cf, const std::string &token) {
// 	cf->tokens.push_back(token);
// 	cf->tokensLine.push_back(cf->line);
// }

// void	master::parser::lineToTokens(t_conf_file *cf, std::string &line) {
// 	bool	endToken = false;
// 	std::string	token = "";
// 	std::string	fline(master::parser::utils::remove_comments_spaces(line));

// 	if (fline.empty())
// 		return ;
// 	for (size_t it = 0; it <= fline.size(); ++it) {
// 		if (isspace(fline[it]) || fline[it] == ';' || it == fline.size()) {
// 			if (fline[it] == ';')
// 				token.push_back(';');
// 			endToken = true;
// 		}
// 		else if (fline[it] == '{')
// 			master::parser::appendToken(cf, "{");
// 		else if (fline[it] == '}')
// 			master::parser::appendToken(cf, "}");
// 		else if (fline[it] != '{' && fline[it] != '}')
// 			token.push_back(fline[it]);
// 		if (endToken == true) {
// 			endToken = false;
// 			if (token.size() > 0 && (token == "server" || token == "location")) {
// 				master::parser::appendToken(cf, token);
// 				token.clear();
// 			}
// 			else if (token.size() > 0)
// 				token.push_back(' ');
// 		}
// 	}
// 	if (token.size() > 0)
// 		master::parser::appendToken(cf, token);
// }

// void	master::parser::readTokens(t_conf_file *cf) {
// 	std::string	line;

// 	while (getline(cf->file, line)) {
// 		// if (fline.size() > 0) {
// 		master::parser::lineToTokens(cf, line);
// 		cf->line++;
// 			// cf->tokens.push_back(fline);
// 			// cf->tokensLine.push_back(cf->currentLine);
// 		// }
// 	}
// 	if (cf->file.bad() == true)
// 		throw (std::runtime_error(Logger::cfFileErr(cf->pathname, std::strerror(errno))));
// #if (PRINT_TOKENS == 1)
// 	std::vector<int>::iterator itInt = cf->tokensLine.begin();
// 	for (std::vector<std::string>::iterator it = cf->tokens.begin(); it != cf->tokens.end(); ++it) {
// 		std::cout << "\t" << *itInt << std::endl;
// 		std::cout << *it << std::endl;
// 		++itInt;
// 	}
// #endif
// }

#include <stdexcept>
#include "parser.hpp"
#include "validations.hpp"

void	master::parser::init_conf(t_conf *cf) {
	static t_conf_file conf_file;
	cf->cline = 1;
	cf->conf_file = &conf_file;
	// init_handler_modules(cf);
}


void	master::parser::parser(t_conf *cf, const char *pathname) {
	int rc = 0;
	if (pathname) {
		cf->conf_file->pathname = pathname;
		validation::validate_file(cf);
	}
	for (;;) {
		rc = conf_read_token(cf);
		if (rc == CONF_BLOCK_DONE)
			throw (std::runtime_error(cf->conf_file->pathname, NULL, "unexpected end of file, expecting \"}\"", cf->cline));
		
	}
// #if (PRINT_TOKENS != 1)
// 	process_tokens(cf);
// #endif
}