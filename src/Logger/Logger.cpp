#include <sstream>
#include "Logger.hpp"

const std::string Logger::cfFileErr(const char *filename, const std::string &err) {
	std::ostringstream oss;
	oss << "webserv: configuration file error: " << filename << " (" << err << ")";
	return oss.str();
}