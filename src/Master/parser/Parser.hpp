#ifndef PARSER_HPP
# define PARSER_HPP

#include <fstream>

namespace Master {
	namespace Parser {
		void	parser(const char *pathname);
		void	readTokens(std::ifstream &file);
	}
}

#endif // PARSER_HPP