#include <sstream>
#include "Logger.hpp"

const std::string Logger::cfFileErr(const char *filename, const std::string &err) {
	std::ostringstream oss;
	oss << "webserv: configuration file error: " << filename << " (" << err << ")";
	return oss.str();
}

const std::string Logger::cfSyntaxErr(const char *filename, const std::string &wrongToken,
const std::string &err, int line) {
	std::ostringstream oss;
	oss << "webserv: \"" << wrongToken << "\" " << err << " in " << filename << ":" << line;
	return (oss.str());
}