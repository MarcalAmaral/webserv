#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
#include "Parser.hpp"
#include "ParserValidations.hpp"
#include "Utils/Utils.hpp"
#include "Logger/Logger.hpp"

using namespace Master;
using namespace std;

void	Parser::parser(const char *pathname) {
	using namespace Parser::Validation;
	t_conf_file cf;

	cf.pathname = pathname;
	validateFile(&cf);
	readTokens(&cf);
}

void	Parser::lineToTokens(t_conf_file *conf, string line) {
	using namespace Logger;
	static int start_line;
	stringstream ss(line);

	Utils::removeComments();
	start_line++;
}

void	Parser::readTokens(t_conf_file *cf) {
	using namespace Logger;
	string	line;

	while (getline(cf->file, line).good() == true) {
		cf->tokens.push_back(line);
		// Parser::lineToTokens(cf, line);
	}
	if (cf->file.fail() == true)
		throw (runtime_error(cfFileErr(cf->pathname, std::strerror(errno))));
	for (vector<string>::iterator it = cf->tokens.begin(); it != cf->tokens.end(); ++it)
		cout << *it << endl;
}
