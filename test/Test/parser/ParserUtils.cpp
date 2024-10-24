#include <iostream>
#include "ParserUtils.hpp"
#include "Utils/Utils.hpp"
#include <cctype>
#include <algorithm>

namespace CommonUtils = Utils;

std::string	Master::Parser::Utils::removeCommentsAndSpaces(const std::string &line) {
	size_t	foundComment = line.find('#');

	if (foundComment != std::string::npos)
		return (CommonUtils::trim(line.substr(0, foundComment)));
	return (CommonUtils::trim(line));
}

// void	Master::Parser::Utils::adjustBracketsLeft(std::string &fline) {
// 	using namespace std;
// 	string::iterator it = find(fline.begin(), fline.end(), '{');

// 	for (;it != fline.end(); it = find(it + 1, fline.end(), '{')) {
// 		if (isspace(*(it - 1)) == false) {
// 			fline.insert(it, ' ');
// 			continue ;
// 		}
// 		else if (isspace(*(it + 1)) == false)
// 			fline.insert(it + 1, ' ');
// 	}
// }