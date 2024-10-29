#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <string>

namespace logger {
	const std::string cf_file_err(const char *filename, const std::string &err);
	const std::string cf_syntax_err(const char *filename, const std::string &err, const std::string &wrongToken, int line);
}

#endif // LOGGER_HPP