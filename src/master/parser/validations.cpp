#include <fstream>
#include <cerrno>
#include <cstring>
#include "parser.hpp" 
#include "validations.hpp"
#include "logger/logger.hpp"

void	master::parser::validation::validate_file(t_conf *cf) {
	cf->conf_file->file.open(cf->conf_file->pathname);
	if (cf->conf_file->file.is_open() == false)
		throw (std::runtime_error(Logger::cf_file_err(cf->conf_file->pathname, std::strerror(errno))));
}