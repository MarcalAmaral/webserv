#include <fstream>
#include <cerrno>
#include <cstring>
#include "Parser.hpp" 
#include "ParserValidations.hpp"
#include "Logger/Logger.hpp"

void	Master::Parser::Validation::validateFile(t_conf_file *conf) {
	conf->file.open(conf->pathname);
	if (conf->file.is_open() == false)
		throw (std::runtime_error(Logger::cfFileErr(conf->pathname, std::strerror(errno))));
}