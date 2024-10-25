#include <stdexcept>
#include <cerrno>
#include <fstream>
#include <cstring>
#include <cctype>
#include "Utils/Utils.hpp"
#include "Logger/Logger.hpp"
#include "Manager.hpp"

using namespace webserv;

Manager::Manager() {}

Manager::~Manager() {}

static void	parser::validation::validate_file(t_conf_file *cf) {
	cf->file.open(cf->filename);
	if (cf->file.is_open() == false)
		throw (std::runtime_error(Logger::cfFileErr(cf->filename, std::strerror(errno))));
};

std::string	parser::utils::remove_comments_and_spaces(const std::string &line) {
	size_t	foundComment = line.find('#');

	if (foundComment != std::string::npos)
		return (Utils::trim(line.substr(0, foundComment)));
	return (Utils::trim(line));
}

void	parser::parser(t_conf_file *cf, char *filename) {
	bool			found = false;
	unsigned int	nline = 1;
	std::string		line;
	std::string		word;

	if (filename) {
		cf->filename = filename;
		validate_file(cf);
	}
	while (getline(cf->file, line)) {
		line = remove_comments_and_spaces(line);
		
		nline++;
	}
	if (cf->file.bad() == true)
		throw (std::runtime_error(Logger::cfFileErr(cf->filename, std::strerror(errno))));
}