#ifndef PARSER_HANDLER_HPP
# define PARSER_HANDLER_HPP

# include "Parser.hpp"
# include "Server.hpp"
# include "Location.hpp"

namespace master {

	inline namespace parser {

		inline namespace handler {

			class HandlerBase {
				private:
					const std::string _cmd;
					const unsigned int _type;
				public:
					HandlerBase(const std::string &cmd, const unsigned int type) : _cmd(cmd), _type(type) {};
					virtual ~HandlerBase() {};
					virtual void *handler(parser::t_conf_file *cf, Server &srv, Location &loc) = 0;
					const std::string &getCmd(void) {return (_cmd);}
					unsigned int getType(void)  {return (_type);}
			};

			class ServerHandler : public HandlerBase {
				public:
					ServerHandler(const std::string &cmd, const unsigned int type) : HandlerBase(cmd, type) {};
					~ServerHandler() {};
					void	*handler(parser::t_conf_file *cf);
			};

			class ListenHandler : public HandlerBase {
				public:
					ListenHandler(const std::string &cmd, const unsigned int type) : HandlerBase(cmd, type) {};
					~ListenHandler() {};
					void	*handler(parser::t_conf_file *cf);
			};

			class ServerNameHandler : public HandlerBase {
				public:
					ServerNameHandler(const std::string &cmd, const unsigned int type) : HandlerBase(cmd, type) {};
					~ServerNameHandler() {};
					void	*handler(parser::t_conf_file *cf);
			};

			class ClientMaxBodySizeHandler : public HandlerBase {
				public:
					ClientMaxBodySizeHandler(const std::string &cmd, const unsigned int type) : HandlerBase(cmd, type) {};
					~ClientMaxBodySizeHandler() {};
					void	*handler(parser::t_conf_file *cf);
			};

			class ErrorPageHandler : public HandlerBase {
				public:
					ErrorPageHandler(const std::string &cmd, const unsigned int type) : HandlerBase(cmd, type) {};
					~ErrorPageHandler() {};
					void	*handler(parser::t_conf_file *cf);
			};

			class LocationHandler : public HandlerBase {
				public:
					LocationHandler(const std::string &cmd, const unsigned int type) : HandlerBase(cmd, type) {};
					~LocationHandler() {};
					void	*handler(parser::t_conf_file *cf);
			};

			class AllowMethodsHandler : public HandlerBase {
				public:
					AllowMethodsHandler(const std::string &cmd, const unsigned int type) : HandlerBase(cmd, type) {};
					~AllowMethodsHandler() {};
					void	*handler(parser::t_conf_file *cf);
			};

			class RedirectHandler : public HandlerBase {
				public:
					RedirectHandler(const std::string &cmd, const unsigned int type) : HandlerBase(cmd, type) {};
					~RedirectHandler() {};
					void	*handler(parser::t_conf_file *cf);
			};

			class RootHandler : public HandlerBase {
				public:
					RootHandler(const std::string &cmd, const unsigned int type) : HandlerBase(cmd, type) {};
					~RootHandler() {};
					void	*handler(parser::t_conf_file *cf);
			};

			class AutoIndexHandler : public HandlerBase {
				public:
					AutoIndexHandler(const std::string &cmd, const unsigned int type) : HandlerBase(cmd, type) {};
					~AutoIndexHandler() {};
					void	*handler(parser::t_conf_file *cf);
			};

			class IndexHandler : public HandlerBase {
				public:
					IndexHandler(const std::string &cmd, const unsigned int type) : HandlerBase(cmd, type) {};
					~IndexHandler() {};
					void	*handler(parser::t_conf_file *cf);
			};

			class CgiHandler : public HandlerBase {
				public:
					CgiHandler(const std::string &cmd, const unsigned int type) : HandlerBase(cmd, type) {};
					~CgiHandler() {};
					void	*handler(parser::t_conf_file *cf);
			};

			class UploadDirHandler : public HandlerBase {
				public:
					UploadDirHandler(const std::string &cmd, const unsigned int type) : HandlerBase(cmd, type) {};
					~UploadDirHandler() {};
					void	*handler(parser::t_conf_file *cf);
			};
			void	init_handler_modules(parser::t_conf_file *cf);
		}
	}
}

#endif // PARSER_HANDLER_HPP	