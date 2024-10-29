#include <string>
#include "Server/Server.hpp"
#include "ParserHandlers.hpp"
#include "Parser.hpp"

using namespace master;

void	parser::handler::init_handler_module(parser::t_conf_file *cf) {
	cf->handlers["server"] = new ServerHandler("server", MAIN_CONF|CONF_NOARGS); 
	cf->handlers["listen"] = new ListenHandler("listen", SRV_CONF|CONF_TAKE1);
	cf->handlers["server_name"] = new ServerNameHandler("server_name", SRV_CONF|CONF_TAKE1);
	cf->handlers["client_max_body_size"] = new CLientMaxBodySize("client_max_body_size", SRV_CONF|CONF_TAKE1);
	cf->handlers["error_page"] = new ErrorPageHandler("error_page", SRV_CONF|CONF_2MORE);
	cf->handlers["location"] = new LocationHandler("location", SRV_CONF|CONF_TAKE1);
	cf->handlers["allow_methods"] = new AllowMethodsHandler("allow_methods", LOC_CONF|CONF_1MORE);
	cf->handlers["redirect"] = new RedirectHandler("redirect", LOC_CONF|CONF_TAKE1);
	cf->handlers["root"] = new RootHandler("root", LOC_CONF|CONF_TAKE1);
	cf->handlers["auto_index"] = new AutoIndexHandler("auto_index", LOC_CONF|CONF_TAKE1);
	cf->handlers["index"] = new IndexHandler("index", LOC_CONF|CONF_TAKE1);
	cf->handlers["cgi"] = new CgiHandler("cgi", LOC_CONF|CONF_1MORE);
	cf->handlers["upload_dir"] = new UploadDirHandler("upload_dir", LOC_CONF|CONF_TAKE1);
}

ServerHandler::handler(parser::t_conf_file *cf, unsigned int state) {
	if (!(state & MAIN_CONF|LOC_CONF))
		throw (std::runtime_error(cf->pathname, *cf->args->begin(), "directive is not allowed here"));
	

}

ListenHandler::handler(parser::t_conf_file *cf) {
	
}

ServerNameHandler::handler(parser::t_conf_file *cf) {
	
}

ClientMaxBodySizeHandler::handler(parser::t_conf_file *cf) {
	
}

ErrorPageHandler::handler(parser::t_conf_file *cf) {
	
}

LocationHandler::handler(parser::t_conf_file *cf) {
	
}

AllowMethodsHandler::handler(parser::t_conf_file *cf) {
	
}

RedirectHandler::handler(parser::t_conf_file *cf) {
	
}

RootHandler::handler(parser::t_conf_file *cf) {
	
}

AutoIndexHandler::handler(parser::t_conf_file *cf) {
	
}

IndexHandler::handler(parser::t_conf_file *cf) {
	
}

CgiHandler::handler(parser::t_conf_file *cf) {
	
}

UploadDirHandler::handler(parser::t_conf_file *cf) {
	
}
