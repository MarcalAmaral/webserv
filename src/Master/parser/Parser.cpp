#include <vector>
#include <fstream>
#include <exception>
#include <iostream>
#include "Parser.hpp"
#include "ParserValidations.hpp"
#include "Utils/Utils.hpp"

using namespace Utils;
using namespace Master;
using namespace std;

void	Parser::parser(const char *pathname) {
	try {
		Parser::Validation::validateFile(pathname);
		ifstream file(pathname);
		Parser::readTokens(file);
	} catch (const exception &e) {
		cerr << e.what() << endl;
		terminate();
	}
}

void	Parser::readTokens(ifstream &file) {
	// short		startDirectiveBlock = 0;
	// ofstream		tokens;
	string			line;
	size_t			foundComment;
	string			formattedLine;
	vector<string>	lines;

	while (getline(file, line).fail() == false) {
		foundComment = line.find('#');
		formattedLine = trim(line);
		if (foundComment) {
			formattedLine = (formattedLine.substr(0, foundComment));
			if (formattedLine[0] != '#' && formattedLine.empty() == false)
				lines.push_back(formattedLine);
			continue ;
		}
		if (formattedLine[0] != '#' && formattedLine.empty() == false)
			lines.push_back(formattedLine);
	}
	// print vector content;
	for (vector<string>::iterator it=lines.begin(); it != lines.end(); ++it)
		std::cout << *it << std::endl;
	return ;
}