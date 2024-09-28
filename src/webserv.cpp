#include "defines.h"
#include "Server/Server.hpp"

int	main(void) {
	try {
		Server server;
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (FAIL);
	}
	return (SUCCESS);
}