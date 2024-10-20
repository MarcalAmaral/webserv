#include "ParserUtils.hpp"
#include "Utils/Utils.hpp"

namespace CommonUtils = Utils;

std::string    Master::Parser::Utils::removeCommentsAndSpaces(const std::string &line) {
	size_t	foundComment = line.find('#');

	if (foundComment != std::string::npos)
		return (CommonUtils::trim(line.substr(0, foundComment)));
	return (CommonUtils::trim(line));
}