#include <iostream>
#include "defines.hpp"
#include "Master/parser/Parser.hpp"

int	main(int ac, char **av) {
	if (ac == 2) {
		try {
			using namespace Master::Parser;
			initConf();
			parser(&Master::Parser::cf, av[1]);
			// Server server;
			// std::string fileName(av[1]);
			// server.parserConfig(fileName);
			// server.initLoopEvent();
		} catch (const std::exception &e) {
			std::cerr << e.what() << std::endl;
			return (FAIL);
		}
	}
	return (SUCCESS);
}