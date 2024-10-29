#include <iostream>
#include "utils.hpp"
#include "utils/utils.hpp"
#include <cctype>
#include <algorithm>

namespace common_utils = utils;

std::string	master::parser::utils::remove_comments_spaces(const std::string &line) {
	size_t	foundComment = line.find('#');

	if (foundComment != std::string::npos)
		return (common_utils::trim(line.substr(0, foundComment)));
	return (common_utils::trim(line));
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