#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <string>

namespace Logger {
	const std::string cfFileErr(const char *filename, const std::string &err);
	const std::string cfSyntaxErr(const char *filename, const std::string &err, const std::string &wrongToken, int line);
}

#endif // LOGGER_HPP