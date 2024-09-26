#include "Server.hpp"

const char *Server::ServerBindSocketException::what() const throw() {
	return ("Error: cannot bind socket");
}

const char *Server::ServerCreateSocketException::what() const throw() {
	return ("Error: cannot create socket");
}

const char *Server::ServerSetSocketOptionsException::what() const throw() {
	return ("Error: cannot set socket options");
}

const char *Server::ServerListenException::what() const throw() {
	return ("Error: cannot set server to listen connections");
}

const char *Server::ServerEPollCreateInstanceException::what() const throw() {
	return ("Error: cannot create epoll instance");
}