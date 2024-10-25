#ifndef PARSER_HANDLER_HPP
# define PARSER_HANDLER_HPP

# include "Parser.hpp"
# include "Server.hpp"
# include "Location.hpp"

namespace master {

	namespace parser {

		inline namespace handler {

			class base {
				private:
					const std::string _cmd;
					const unsigned int _type;
				public:
					HandlerClass(const std::string &cmd, const unsigned int type) : _cmd(cmd), _type(type) {};
					virtual ~HandlerClass() {};
					virtual void *handler(Parser::t_conf_file *cf, Server &srv, Location &loc) = 0;
					const std::string &getCmd(void) {return (_cmd);}
					unsigned int getType(void)  {return (_type);}
			};

			class ServerHandler : public HandlerClass {
				public:
					ServerHandler(const std::string &cmd, const unsigned int type) : HandlerClass(cmd, type) {};
					~ServerHandler();
					void	*handler(Parser::t_conf_file *cf);
			};

			class ListenHandler : public HandlerClass {
				public:
					ListenHandler(const std::string &cmd, const unsigned int type) : HandlerClass(cmd, type) {};
					~ListenHandler();
					void	*handler(Parser::t_conf_file *cf);
			};

			class ServerNameHandler : public HandlerClass {
				public:
					ServerNameHandler(const std::string &cmd, const unsigned int type) : HandlerClass(cmd, type) {};
					~ServerNameHandler();
					void	*handler(Parser::t_conf_file *cf);
			};

			class ClientMaxBodySizeHandler : public HandlerClass {
				public:
					ClientMaxBodySizeHandler(const std::string &cmd, const unsigned int type) : HandlerClass(cmd, type) {};
					~ClientMaxBodySizeHandler();
					void	*handler(Parser::t_conf_file *cf);
			};

			class ErrorPageHandler : public HandlerClass {
				public:
					ErrorPageHandler(const std::string &cmd, const unsigned int type) : HandlerClass(cmd, type) {};
					~ErrorPageHandler();
					void	*handler(Parser::t_conf_file *cf);
			};

			class LocationHandler : public HandlerClass {
				public:
					LocationHandler(const std::string &cmd, const unsigned int type) : HandlerClass(cmd, type) {};
					~LocationHandler();
					void	*handler(Parser::t_conf_file *cf);
			};

			class AllowMethodsHandler : public HandlerClass {
				public:
					AllowMethodsHandler(const std::string &cmd, const unsigned int type) : HandlerClass(cmd, type) {};
					~AllowMethodsHandler();
					void	*handler(Parser::t_conf_file *cf);
			};

			class RedirectHandler : public HandlerClass {
				public:
					RedirectHandler(const std::string &cmd, const unsigned int type) : HandlerClass(cmd, type) {};
					~RedirectHandler();
					void	*handler(Parser::t_conf_file *cf);
			};

			class RootHandler : public HandlerClass {
				public:
					RootHandler(const std::string &cmd, const unsigned int type) : HandlerClass(cmd, type) {};
					~RootHandler();
					void	*handler(Parser::t_conf_file *cf);
			};

			class AutoIndexHandler : public HandlerClass {
				public:
					AutoIndexHandler(const std::string &cmd, const unsigned int type) : HandlerClass(cmd, type) {};
					~AutoIndexHandler() {};
					void	*handler(Parser::t_conf_file *cf);
			};

			class IndexHandler : public HandlerClass {
				public:
					IndexHandler(const std::string &cmd, const unsigned int type) : HandlerClass(cmd, type) {};
					~IndexHandler();
					void	*handler(Parser::t_conf_file *cf);
			};

			class CgiHandler : public HandlerClass {
				public:
					CgiHandler(const std::string &cmd, const unsigned int type) : HandlerClass(cmd, type) {};
					~CgiHandler();
					void	*handler(Parser::t_conf_file *cf);
			};

			class UploadDirHandler : public HandlerClass {
				public:
					UploadDirHandler(const std::string &cmd, const unsigned int type) : HandlerClass(cmd, type) {};
					~UploadDirHandler();
					void	*handler(Parser::t_conf_file *cf);
			};
			void	init_handler_modules(Parser::t_conf_file *cf);
		}
	}
}

#endif // PARSER_HANDLER_HPP	