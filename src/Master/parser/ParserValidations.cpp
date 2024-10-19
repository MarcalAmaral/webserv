#include <fstream>
#include <cerrno>
#include <cstring>
#include "Parser.hpp" 
#include "ParserValidations.hpp"
#include "Logger/Logger.hpp"

using namespace std;

void	Master::Parser::Validation::validateFile(t_conf_file *conf) {
	using namespace Logger;

	conf->file.open(conf->pathname);
	if (conf->file.is_open() == false)
		throw (runtime_error(confFileErr(conf->pathname, std::strerror(errno))));
}