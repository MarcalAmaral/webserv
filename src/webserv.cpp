#include <iostream>
#include "defines.hpp"
#include "Server/Server.hpp"

int	main(void) {
	try {
		Server server;
		server.initLoopEvent();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (FAIL);
	}
	return (SUCCESS);
}