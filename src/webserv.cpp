#include <iostream>
#include "defines.hpp"
#include "Manager/Manager.hpp"
// #include "Master/parser/Parser.hpp"

int	main(int ac, char **av) {
	if (ac == 2) {
		try {
			webserv::t_conf_file cf;
			webserv::init_conf_file(&cf);
			webserv::Manager *manager = webserv::parser::parser(&cf, av[1]);
			// initConf(&cf);
			// parser(&cf, av[1]);
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