#include <iostream>
#include "defines.hpp"
#include "Server/Server.hpp"

int	main(int ac, char **av) {
	if (ac == 2) {
		try {
			Server server;
			std::string fileName(av[1]);
			server.parserConfig(fileName);
			server.initLoopEvent();
		} catch (const std::exception &e) {
			std::cerr << e.what() << std::endl;
			return (FAIL);
		}
	}
	return (SUCCESS);
}