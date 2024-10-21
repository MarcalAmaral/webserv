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

void	Master::Parser::Utils::adjustBrackets(std::string &fline) {
	using namespace std;
	string::iterator leftBracket = find(fline.begin(), fline.end(), '{');
	string::iterator rightBracket = find(fline.begin(), fline.end(), '}');

	while (leftBracket != fline.end()) {
		if (leftBracket != fline.begin()) {
			if (isspace(*(leftBracket - 1)) == false) {
				fline.insert(leftBracket - 1, ' ');
				leftBracket++;
			}
		}
		if ((leftBracket + 1) != fline.end()) {
			if (isspace(*(leftBracket + 1)) == false)
				fline.insert(leftBracket + 1, ' ');
		}
		if ((leftBracket + 1) != fline.end())
			leftBracket = find(leftBracket + 1, fline.end(), '{');
		else
			leftBracket = fline.end();
	}
	cout << fline << endl;
	while (rightBracket != fline.end()) {
		if (rightBracket != fline.begin()) {
			if (isspace(*(rightBracket - 1)) == false) {
				cout << *rightBracket << endl;
				fline.insert(rightBracket - 1, ' ');
				rightBracket++;
			}
		}
		if ((rightBracket + 1) != fline.end()) {
			if (isspace(*(rightBracket + 1)) == false) {
				cout << *rightBracket << endl;
				fline.insert(rightBracket + 1, ' ');
			}
		}
		if ((rightBracket + 1) != fline.end())
			rightBracket = find(rightBracket + 1, fline.end(), '}');
		else
			rightBracket = fline.end();
	}
	// while (rightBracket != string::npos) {
	// 	if (isspace(fline[rightBracket - 1]) == false)
	// 		fline.insert(rightBracket - 1, ' ');
	// 	if (fline[rightBracket + 1] != string::npos)
	// 		if (isspace(fline[rightBracket + 1]) == false)
	// 			fline.insert(rightBracket + 1, ' ');
	// 	rightBracket = fline.find('}');
	// }
}