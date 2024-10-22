#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
#include <cctype>
#include "Parser.hpp"
#include "ParserValidations.hpp"
#include "ParserUtils.hpp"
#include "Utils/Utils.hpp"
#include "Logger/Logger.hpp"

using namespace Master;
using namespace std;

static t_conf_commands modulesConf[] = {
	{
		"server",
		Parser::WS_HTTP_MAIN_CONF|Parser::WS_CONF_BLOCK|Parser::WS_CONF_NOARGS,
		Parser::handleServer
	},
	{
		"location",
		Parser::WS_HTTP_SRV_CONF|Parser::WS_CONF_BLOCK|Parser::WS_CONF_TAKE1,
		Parser::handleLocation
	},
	{
		"server_name",
		Parser::WS_HTTP_SRV_CONF|Parser::WS_CONF_TAKE1,
		Parser::handleServerName
	},
	{
		"client_max_body_size",
		Parser::WS_HTTP_SRV_CONF|Parser::WS_CONF_TAKE1,
		Parser::handleClientMaxBodySize
	},
	{
		"error_page",
		Parser::WS_HTTP_SRV_CONF|Parser::WS_CONF_2MORE,
		Parser::handleErrorPage
	},
	{
		"allow_methods",
		Parser::WS_HTTP_LOC_CONF|Parser::WS_CONF_1MORE,
		Parser::handleLocationAllowMethods
	},
	{
		"redirect",
		Parser::WS_HTTP_LOC_CONF|Parser::WS_CONF_TAKE1,
		Parser::handleLocationRedirect
	},
	{
		"root",
	},
	{
		"autoindex"
	},
	{
		"index",
	},
	{
		"upload_dir"
	},
};

void	Parser::parser(const char *pathname) {
	using namespace Parser::Validation;
	t_conf_file cf;

	cf.currentLine = 0;
	cf.pathname = pathname;
	validateFile(&cf);
	readTokens(&cf);
	processTokens(&cf);
}

void	Parser::handleServer(t_conf_file *cf, vector<string>::iterator &it, vector<int>::iterator &curLine) {
	if (*it != "{")
		throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, "unexpected", *it, *curLine)));
	return ;
}

// Parser::Directive::Directive(vector<string>::iterator &f, vector<string>::iterator &l, enum e_context type) {
// 	for (;f != l; ++f) {
// 		_elts.push_back(*f);
// 	}
// 	_type = type;
// }

void	Parser::delimitingDirectives(t_conf_file *cf) {
	for (vector<string>::iterator it=cf->tokens.begin(); it != cf->tokens.end(); ++it) {
		
	}
}

bool	Parser::checkDirectives(string &directive, enum e_context type) {
	const string directives[13] = {"server", "listen", "server_name",
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

void	Parser::processTokens(t_conf_file *cf) {
	enum e_context context;
	bool	startServerBlock = false;
	vector<int>::iterator itLine = cf->tokensLine.begin();

	for (vector<string>::iterator it=cf->tokens.begin(); it != cf->tokens.end(); ++it) {
		if (context == HTTP) {
			if (*it == "server")
				context = SERVER;
			else if (checkDirectives(*it, Parser::ALL))
				throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "directive is not allowed here", *itLine)));
			else
				throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "unknown directive", *itLine)));

		} else if (context == SERVER) {
			if (startServerBlock == false && *it == "{")
				startServerBlock == true;
			else if (startServerBlock == true && *it == "{")
				throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "unexpected", *itLine)));
			else if (startServerBlock == true && *it == "}")
				startServerBlock == false;
			else if (startServerBlock == false && *it == "}")
				throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "unexpected", *itLine)));
			else if (checkDirectives(*it, Parser::ALL) == true) {
				if (checkDirectives(*it, Parser::SERVER) == false)
					throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "directive is not allowed here", *itLine)));
				if (*it == "location")
					context = LOCATION;
				cf->handlers[*it].handler(cf, it, itLine);
			}
			else
				throw (runtime_error(Logger::cfSyntaxErr(cf->pathname, *it, "unknown directive", *itLine)));
			
		} else if (context == LOCATION) {
			continue ;
		}
		++itLine;
	}
}

// void    Parser::processTokens(t_conf_file *cf) {
// 	using namespace Parser;

// 	int		nServers = 0;
// 	vector<int>::iterator curLine = cf->tokensLine.begin();
// 	for (vector<string>::iterator it = cf->tokens.begin(); it != cf->tokens.end(); ++it) {
// 		if (*it == "server") {
// 			nServers++;
// 			it++;
// 			curLine++;
// 			Parser::handleServer(cf, it, curLine);	
// 		}
// 		else if (*it == "{")
// 			continue ;
// 		curLine++;
// 	}
// 	if (nServers == 0)
// 		throw (runtime_error(Logger::cfFileErr(cf->pathname, "server directive not found")));
// }

void	Parser::appendToken(t_conf_file *cf, const string &token) {
	cf->tokens.push_back(token);
	cf->tokensLine.push_back(cf->currentLine);
}

void	Parser::lineToTokens(t_conf_file *cf, string &line) {
	bool	endToken = false;
	string	token = "";
	string	fline(Parser::Utils::removeCommentsAndSpaces(line));

	if (fline.empty())
		return ;
	for (size_t it = 0; it <= fline.size(); ++it) {
		// cout << fline[it] << endl;
		if (isspace(fline[it]) || fline[it] == ';' || it == fline.size()) {
			if (fline[it] == ';')
				token.push_back(';');
			endToken = true;
		}
		else if (fline[it] == '{')
			Parser::appendToken(cf, "{");
		else if (fline[it] == '}')
			Parser::appendToken(cf, "}");
		else if (fline[it] != '{' && fline[it] != '}')
			token.push_back(fline[it]);
		if (endToken == true) {
			if (token.size() > 0)
				Parser::appendToken(cf, token);
			endToken = false;
			token.clear();
		}
	}
}

// void	Parser::lineToTokens(t_conf_file *cf, string &line) {
	// using namespace Logger;
	// stringstream    ss;
	// string			formattedToken;
	// string          formattedLine;
	// string          token;
// 
	// formattedLine = Parser::Utils::removeCommentsAndSpaces(line);
	// Parser::Utils::adjustBracketsLeft(formattedLine);
	// if (formattedLine.empty() == true)
		// return ;
	// ss.str(formattedLine);
	// while (ss.fail() == false) {
		// ss >> ws >> token;
		// if (token.size() > 0) {
			// cf->tokensLine.push_back(cf->currentLine);
			// cf->tokens.push_back(token);
		// }
		// token.clear();
	// }
	// return ;
// }

void	Parser::readTokens(t_conf_file *cf) {
	using namespace Logger;
	string	line;

	while (getline(cf->file, line)) {
		cf->currentLine++;
		Parser::lineToTokens(cf, line);
	}
	if (cf->file.bad() == true)
		throw (runtime_error(cfFileErr(cf->pathname, std::strerror(errno))));
	// vector<int>::iterator itInt = cf->tokensLine.begin();
	// for (vector<string>::iterator it = cf->tokens.begin(); it != cf->tokens.end(); ++it) {
	// 	cout << "\t" << *itInt << endl;
	// 	cout << *it << endl;
	// 	++itInt;
	// }
}
