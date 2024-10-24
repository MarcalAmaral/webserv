#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
#include <cctype>
#include "Parser.hpp"
#include "ParserValidations.hpp"
// #include "ParserHandlers.hpp"
#include "ParserUtils.hpp"
#include "Utils/Utils.hpp"
#include "Logger/Logger.hpp"

void	Master::Parser::initConf(t_conf_file *cf) {
	using namespace Master::Parser;
	cf->line = 1;
	cf->pathname = NULL;
}

// void	*handlerDirective(t_conf_file *cf) {

// }

void	Master::Parser::parser(t_conf_file *cf, const char *pathname) {
	using namespace Master::Parser;

	if (pathname) {
		cf->pathname = pathname;
		Validation::validateFile(cf);
		readTokens(cf);
	}
#if (PRINT_TOKENS != 1)
	processTokens(cf);
#endif
}

void	Master::Parser::processTokens(t_conf_file *cf) {
	using namespace Master::Parser;
	using namespace Logger;
	enum {
		main,
		srv,
		loc
	} context;
	bool	onBlock = false;
	std::vector<int>::iterator cline = cf->tokensLine.begin();

	context = main;
	for (std::vector<std::string>::iterator it=cf->tokens.begin(); it != cf->tokens.end(); ++it) {
		if (context == main) {
			if (checkDirectives(*it, ALL)) {
				if (*it == "server") {
					cf->handlers[*it]->handler(cf, NULL, );

				}
				else
					throw (std::runtime_error(cfSynxtaxErr(cf->pathname, *it, "directive not allow here")))
			}
		} else if (context = srv) {

		} else if (context = loc) {

		}
		cline++;
		// for (std::string::iterator ch=it->begin(); ch != it->end(); ++ch) {

		// }
	}
}

bool	Master::Parser::checkDirectives(std::string &directive, enum e_context type) {
	const std::string directives[13] = {"server", "listen", "server_name",
	"client_max_body_size", "error_page", "location", "allow_methods", "redirect", "root",
	"autoindex", "index", "cgi", "upload_dir"};

	if (type == Parser::ALL) {
		for (int i = 0; i < 13; ++i) {
			if (directive == directives[i])
				return true;
		}
	} else if (type == Parser::HTTP) {
		for (int i = 0; i < 1; ++i) {
			if (directive == directives[i])
				return true;
		}
	} else if (type == Parser::SERVER) {
		for (int i = 1; i < 6; ++i) {
			if (directive == directives[i])
				return true;
		}
	} else if (type == Parser::LOCATION) {
		for (int i = 7; i < 13; ++i) {
			if (directive == directives[i])
				return true;
		}
	}
	return false;
}

// void	Parser::processTokens(t_conf_file *cf) {
// 	enum e_context context;
// 	bool	startServerBlock = false;
// 	vector<int>::iterator itLine = cf->tokensLine.begin();

// 	for (vector<string>::iterator it=cf->tokens.begin(); it != cf->tokens.end(); ++it) {
// 		if (context == HTTP) {
// 			if (*it == "server")
// 				context = SERVER;
// 			else if (checkDirectives(*it, Parser::ALL))
// 				throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "directive is not allowed here", *itLine)));
// 			else
// 				throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "unknown directive", *itLine)));

// 		} else if (context == SERVER) {
// 			if (startServerBlock == false && *it == "{")
// 				startServerBlock = true;
// 			else if (startServerBlock == true && *it == "{")
// 				throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "unexpected", *itLine)));
// 			else if (startServerBlock == true && *it == "}")
// 				startServerBlock = false;
// 			else if (startServerBlock == false && *it == "}")
// 				throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "unexpected", *itLine)));
// 			else if (checkDirectives(*it, Parser::ALL) == true) {
// 				if (checkDirectives(*it, Parser::SERVER) == false)
// 					throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "directive is not allowed here", *itLine)));
// 				if (*it == "location")
// 					context = LOCATION;
// 				// cf->handlers[*it].handler(cf, it, itLine);
// 			}
// 			else
// 				throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "unknown directive", *itLine)));
			
// 		} else if (context == LOCATION) {
// 			continue ;
// 		}
// 		++itLine;
// 	}
// }

void	Master::Parser::appendToken(t_conf_file *cf, const std::string &token) {
	cf->tokens.push_back(token);
	cf->tokensLine.push_back(cf->line);
}

void	Master::Parser::lineToTokens(t_conf_file *cf, std::string &line) {
	bool	endToken = false;
	std::string	token = "";
	std::string	fline(Master::Parser::Utils::removeCommentsAndSpaces(line));

	if (fline.empty())
		return ;
	for (size_t it = 0; it <= fline.size(); ++it) {
		if (isspace(fline[it]) || fline[it] == ';' || it == fline.size()) {
			if (fline[it] == ';')
				token.push_back(';');
			endToken = true;
		}
		else if (fline[it] == '{')
			Master::Parser::appendToken(cf, "{");
		else if (fline[it] == '}')
			Master::Parser::appendToken(cf, "}");
		else if (fline[it] != '{' && fline[it] != '}')
			token.push_back(fline[it]);
		if (endToken == true) {
			endToken = false;
			if (token.size() > 0 && (token == "server" || token == "location")) {
				Master::Parser::appendToken(cf, token);
				token.clear();
			}
			else if (token.size() > 0)
				token.push_back(' ');
		}
	}
	if (token.size() > 0)
		Master::Parser::appendToken(cf, token);
}

void	Master::Parser::readTokens(t_conf_file *cf) {
	std::string	line;

	while (getline(cf->file, line)) {
		// if (fline.size() > 0) {
		Master::Parser::lineToTokens(cf, line);
		cf->line++;
			// cf->tokens.push_back(fline);
			// cf->tokensLine.push_back(cf->currentLine);
		// }
	}
	if (cf->file.bad() == true)
		throw (std::runtime_error(Logger::cfFileErr(cf->pathname, std::strerror(errno))));
#if (PRINT_TOKENS == 1)
	std::vector<int>::iterator itInt = cf->tokensLine.begin();
	for (std::vector<std::string>::iterator it = cf->tokens.begin(); it != cf->tokens.end(); ++it) {
		std::cout << "\t" << *itInt << std::endl;
		std::cout << *it << std::endl;
		++itInt;
	}
#endif
}
