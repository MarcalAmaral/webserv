#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
#include <cctype>
#include "Parser.hpp"
#include "ParserValidations.hpp"
#include "ParserUtils.hpp"
#include "Utils/Utils.hpp"
#include "Logger/Logger.hpp"

using namespace Master;
using namespace std;

void	Parser::parser(const char *pathname) {
	using namespace Parser::Validation;
	t_conf_file cf;

	cf.currentLine = 0;
	cf.pathname = pathname;
	validateFile(&cf);
	readTokens(&cf);
	processTokens(&cf);
}

void	Parser::handleServer(t_conf_file *cf, vector<string>::iterator &it) {
	(void)cf;
	return ;
}

void    Parser::processTokens(t_conf_file *cf) {
	using namespace Parser;
	using namespace Logger;

	int		nServers = 0;
	for (vector<string>::iterator it = cf->tokens.begin(); it != cf->tokens.end(); ++it) {
		if (*it == "server") {
			nServers++;
			Parser::handleServer(cf, it);	
		}
	}
	if (nServers == 0)
		throw (runtime_error(cfFileErr(cf->pathname, "server directive not found")));
}

void	Parser::appendToken(t_conf_file *cf, const string &token) {
	cf->tokens.push_back(token);
	cf->tokensLine.push_back(cf->currentLine);
}

void	Parser::lineToTokens(t_conf_file *cf, string &line) {
	bool	endToken = false;
	string	token = "";
	string fline(Parser::Utils::removeCommentsAndSpaces(line));

	if (fline.empty())
		return ;
	for (size_t it = 0; it <= fline.size(); ++it) {
		// cout << fline[it] << endl;
		if (isspace(fline[it]) || fline[it] == ';' || it == fline.size()) {
			if (fline[it] == ';')
				token.push_back(';');
			endToken = true;
		}
		else if (fline[it] == '{')
			Parser::appendToken(cf, "{");
		else if (fline[it] == '}')
			Parser::appendToken(cf, "}");
		else if (fline[it] != '{' && fline[it] != '}')
			token.push_back(fline[it]);
		if (endToken == true) {
			if (token.size() > 0)
				Parser::appendToken(cf, token);
			endToken = false;
			token.clear();
		}
	}
}

// void	Parser::lineToTokens(t_conf_file *cf, string &line) {
	// using namespace Logger;
	// stringstream    ss;
	// string			formattedToken;
	// string          formattedLine;
	// string          token;
// 
	// formattedLine = Parser::Utils::removeCommentsAndSpaces(line);
	// Parser::Utils::adjustBracketsLeft(formattedLine);
	// if (formattedLine.empty() == true)
		// return ;
	// ss.str(formattedLine);
	// while (ss.fail() == false) {
		// ss >> ws >> token;
		// if (token.size() > 0) {
			// cf->tokensLine.push_back(cf->currentLine);
			// cf->tokens.push_back(token);
		// }
		// token.clear();
	// }
	// return ;
// }

void	Parser::readTokens(t_conf_file *cf) {
	using namespace Logger;
	string	line;

	while (getline(cf->file, line)) {
		cf->currentLine++;
		Parser::lineToTokens(cf, line);
	}
	if (cf->file.bad() == true)
		throw (runtime_error(cfFileErr(cf->pathname, std::strerror(errno))));
	vector<int>::iterator itInt = cf->tokensLine.begin();
	for (vector<string>::iterator it = cf->tokens.begin(); it != cf->tokens.end(); ++it) {
		cout << "\t" << *itInt << endl;
		cout << *it << endl;
		++itInt;
	}
}

// char *
// ngx_conf_parse(ngx_conf_t *cf, ngx_str_t *filename)
// {
//     char             *rv;
//     ngx_fd_t          fd;
//     ngx_int_t         rc;
//     ngx_buf_t         buf;
//     ngx_conf_file_t  *prev, conf_file;
//     enum {
//         parse_file = 0,
//         parse_block,
//         parse_param
//     } type;

// #if (NGX_SUPPRESS_WARN)
//     fd = NGX_INVALID_FILE;
//     prev = NULL;
// #endif

//     if (filename) {

//         /* open configuration file */

//         fd = ngx_open_file(filename->data, NGX_FILE_RDONLY, NGX_FILE_OPEN, 0);

//         if (fd == NGX_INVALID_FILE) {
//             ngx_conf_log_error(NGX_LOG_EMERG, cf, ngx_errno,
//                                ngx_open_file_n " \"%s\" failed",
//                                filename->data);
//             return NGX_CONF_ERROR;
//         }

//         prev = cf->conf_file;

//         cf->conf_file = &conf_file;

//         if (ngx_fd_info(fd, &cf->conf_file->file.info) == NGX_FILE_ERROR) {
//             ngx_log_error(NGX_LOG_EMERG, cf->log, ngx_errno,
//                           ngx_fd_info_n " \"%s\" failed", filename->data);
//         }

//         cf->conf_file->buffer = &buf;

//         buf.start = ngx_alloc(NGX_CONF_BUFFER, cf->log);
//         if (buf.start == NULL) {
//             goto failed;
//         }

//         buf.pos = buf.start;
//         buf.last = buf.start;
//         buf.end = buf.last + NGX_CONF_BUFFER;
//         buf.temporary = 1;

//         cf->conf_file->file.fd = fd;
//         cf->conf_file->file.name.len = filename->len;
//         cf->conf_file->file.name.data = filename->data;
//         cf->conf_file->file.offset = 0;
//         cf->conf_file->file.log = cf->log;
//         cf->conf_file->line = 1;

//         type = parse_file;

//         if (ngx_dump_config
// #if (NGX_DEBUG)
//             || 1
// #endif
//            )
//         {
//             if (ngx_conf_add_dump(cf, filename) != NGX_OK) {
//                 goto failed;
//             }

//         } else {
//             cf->conf_file->dump = NULL;
//         }

//     } else if (cf->conf_file->file.fd != NGX_INVALID_FILE) {

//         type = parse_block;

//     } else {
//         type = parse_param;
//     }


//     for ( ;; ) {
//         rc = ngx_conf_read_token(cf);

//         /*
//          * ngx_conf_read_token() may return
//          *
//          *    NGX_ERROR             there is error
//          *    NGX_OK                the token terminated by ";" was found
//          *    NGX_CONF_BLOCK_START  the token terminated by "{" was found
//          *    NGX_CONF_BLOCK_DONE   the "}" was found
//          *    NGX_CONF_FILE_DONE    the configuration file is done
//          */

//         if (rc == NGX_ERROR) {
//             goto done;
//         }

//         if (rc == NGX_CONF_BLOCK_DONE) {

//             if (type != parse_block) {
//                 ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "unexpected \"}\"");
//                 goto failed;
//             }

//             goto done;
//         }

//         if (rc == NGX_CONF_FILE_DONE) {

//             if (type == parse_block) {
//                 ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
//                                    "unexpected end of file, expecting \"}\"");
//                 goto failed;
//             }

//             goto done;
//         }

//         if (rc == NGX_CONF_BLOCK_START) {

//             if (type == parse_param) {
//                 ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
//                                    "block directives are not supported "
//                                    "in -g option");
//                 goto failed;
//             }
//         }

//         /* rc == NGX_OK || rc == NGX_CONF_BLOCK_START */

//         if (cf->handler) {

//             /*
//              * the custom handler, i.e., that is used in the http's
//              * "types { ... }" directive
//              */

//             if (rc == NGX_CONF_BLOCK_START) {
//                 ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "unexpected \"{\"");
//                 goto failed;
//             }

//             rv = (*cf->handler)(cf, NULL, cf->handler_conf);
//             if (rv == NGX_CONF_OK) {
//                 continue;
//             }

//             if (rv == NGX_CONF_ERROR) {
//                 goto failed;
//             }

//             ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "%s", rv);

//             goto failed;
//         }


//         rc = ngx_conf_handler(cf, rc);

//         if (rc == NGX_ERROR) {
//             goto failed;
//         }
//     }

// failed:

//     rc = NGX_ERROR;

// done:

//     if (filename) {
//         if (cf->conf_file->buffer->start) {
//             ngx_free(cf->conf_file->buffer->start);
//         }

//         if (ngx_close_file(fd) == NGX_FILE_ERROR) {
//             ngx_log_error(NGX_LOG_ALERT, cf->log, ngx_errno,
//                           ngx_close_file_n " %s failed",
//                           filename->data);
//             rc = NGX_ERROR;
//         }

//         cf->conf_file = prev;
//     }

//     if (rc == NGX_ERROR) {
//         return NGX_CONF_ERROR;
//     }

//     return NGX_CONF_OK;
// }


// static ngx_int_t
// ngx_conf_handler(ngx_conf_t *cf, ngx_int_t last)
// {
//     char           *rv;
//     void           *conf, **confp;
//     ngx_uint_t      i, found;
//     ngx_str_t      *name;
//     ngx_command_t  *cmd;

//     name = cf->args->elts;

//     found = 0;

//     for (i = 0; cf->cycle->modules[i]; i++) {

//         cmd = cf->cycle->modules[i]->commands;
//         if (cmd == NULL) {
//             continue;
//         }

//         for ( /* void */ ; cmd->name.len; cmd++) {

//             if (name->len != cmd->name.len) {
//                 continue;
//             }

//             if (ngx_strcmp(name->data, cmd->name.data) != 0) {
//                 continue;
//             }

//             found = 1;

//             if (cf->cycle->modules[i]->type != NGX_CONF_MODULE
//                 && cf->cycle->modules[i]->type != cf->module_type)
//             {
//                 continue;
//             }

//             /* is the directive's location right ? */

//             if (!(cmd->type & cf->cmd_type)) {
//                 continue;
//             }

//             if (!(cmd->type & NGX_CONF_BLOCK) && last != NGX_OK) {
//                 ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
//                                   "directive \"%s\" is not terminated by \";\"",
//                                   name->data);
//                 return NGX_ERROR;
//             }

//             if ((cmd->type & NGX_CONF_BLOCK) && last != NGX_CONF_BLOCK_START) {
//                 ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
//                                    "directive \"%s\" has no opening \"{\"",
//                                    name->data);
//                 return NGX_ERROR;
//             }

//             /* is the directive's argument count right ? */

//             if (!(cmd->type & NGX_CONF_ANY)) {

//                 if (cmd->type & NGX_CONF_FLAG) {

//                     if (cf->args->nelts != 2) {
//                         goto invalid;
//                     }

//                 } else if (cmd->type & NGX_CONF_1MORE) {

//                     if (cf->args->nelts < 2) {
//                         goto invalid;
//                     }

//                 } else if (cmd->type & NGX_CONF_2MORE) {

//                     if (cf->args->nelts < 3) {
//                         goto invalid;
//                     }

//                 } else if (cf->args->nelts > NGX_CONF_MAX_ARGS) {

//                     goto invalid;

//                 } else if (!(cmd->type & argument_number[cf->args->nelts - 1]))
//                 {
//                     goto invalid;
//                 }
//             }

//             /* set up the directive's configuration context */

//             conf = NULL;

//             if (cmd->type & NGX_DIRECT_CONF) {
//                 conf = ((void **) cf->ctx)[cf->cycle->modules[i]->index];

//             } else if (cmd->type & NGX_MAIN_CONF) {
//                 conf = &(((void **) cf->ctx)[cf->cycle->modules[i]->index]);

//             } else if (cf->ctx) {
//                 confp = *(void **) ((char *) cf->ctx + cmd->conf);

//                 if (confp) {
//                     conf = confp[cf->cycle->modules[i]->ctx_index];
//                 }
//             }

//             rv = cmd->set(cf, cmd, conf);

//             if (rv == NGX_CONF_OK) {
//                 return NGX_OK;
//             }

//             if (rv == NGX_CONF_ERROR) {
//                 return NGX_ERROR;
//             }

//             ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
//                                "\"%s\" directive %s", name->data, rv);

//             return NGX_ERROR;
//         }
//     }

//     if (found) {
//         ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
//                            "\"%s\" directive is not allowed here", name->data);

//         return NGX_ERROR;
//     }

//     ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
//                        "unknown directive \"%s\"", name->data);

//     return NGX_ERROR;

// invalid:

//     ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
//                        "invalid number of arguments in \"%s\" directive",
//                        name->data);

//     return NGX_ERROR;
// }

// static ngx_int_t
// ngx_conf_read_token(ngx_conf_t *cf)
// {
//     u_char      *start, ch, *src, *dst;
//     off_t        file_size;
//     size_t       len;
//     ssize_t      n, size;
//     ngx_uint_t   found, need_space, last_space, sharp_comment, variable;
//     ngx_uint_t   quoted, s_quoted, d_quoted, start_line;
//     ngx_str_t   *word;
//     ngx_buf_t   *b, *dump;

//     found = 0;
//     need_space = 0;
//     last_space = 1;
//     sharp_comment = 0;
//     variable = 0;
//     quoted = 0;
//     s_quoted = 0;
//     d_quoted = 0;

//     cf->args->nelts = 0;
//     b = cf->conf_file->buffer;
//     dump = cf->conf_file->dump;
//     start = b->pos;
//     start_line = cf->conf_file->line;

//     file_size = ngx_file_size(&cf->conf_file->file.info);

//     for ( ;; ) {

//         if (b->pos >= b->last) {

//             if (cf->conf_file->file.offset >= file_size) {

//                 if (cf->args->nelts > 0 || !last_space) {

//                     if (cf->conf_file->file.fd == NGX_INVALID_FILE) {
//                         ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
//                                            "unexpected end of parameter, "
//                                            "expecting \";\"");
//                         return NGX_ERROR;
//                     }

//                     ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
//                                        "unexpected end of file, "
//                                        "expecting \";\" or \"}\"");
//                     return NGX_ERROR;
//                 }

//                 return NGX_CONF_FILE_DONE;
//             }

//             len = b->pos - start;

//             if (len == NGX_CONF_BUFFER) {
//                 cf->conf_file->line = start_line;

//                 if (d_quoted) {
//                     ch = '"';

//                 } else if (s_quoted) {
//                     ch = '\'';

//                 } else {
//                     ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
//                                        "too long parameter \"%*s...\" started",
//                                        10, start);
//                     return NGX_ERROR;
//                 }

//                 ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
//                                    "too long parameter, probably "
//                                    "missing terminating \"%c\" character", ch);
//                 return NGX_ERROR;
//             }

//             if (len) {
//                 ngx_memmove(b->start, start, len);
//             }

//             size = (ssize_t) (file_size - cf->conf_file->file.offset);

//             if (size > b->end - (b->start + len)) {
//                 size = b->end - (b->start + len);
//             }

//             n = ngx_read_file(&cf->conf_file->file, b->start + len, size,
//                               cf->conf_file->file.offset);

//             if (n == NGX_ERROR) {
//                 return NGX_ERROR;
//             }

//             if (n != size) {
//                 ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
//                                    ngx_read_file_n " returned "
//                                    "only %z bytes instead of %z",
//                                    n, size);
//                 return NGX_ERROR;
//             }

//             b->pos = b->start + len;
//             b->last = b->pos + n;
//             start = b->start;

//             if (dump) {
//                 dump->last = ngx_cpymem(dump->last, b->pos, size);
//             }
//         }

//         ch = *b->pos++;

//         if (ch == LF) {
//             cf->conf_file->line++;

//             if (sharp_comment) {
//                 sharp_comment = 0;
//             }
//         }

//         if (sharp_comment) {
//             continue;
//         }

//         if (quoted) {
//             quoted = 0;
//             continue;
//         }

//         if (need_space) {
//             if (ch == ' ' || ch == '\t' || ch == CR || ch == LF) {
//                 last_space = 1;
//                 need_space = 0;
//                 continue;
//             }

//             if (ch == ';') {
//                 return NGX_OK;
//             }

//             if (ch == '{') {
//                 return NGX_CONF_BLOCK_START;
//             }

//             if (ch == ')') {
//                 last_space = 1;
//                 need_space = 0;

//             } else {
//                 ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
//                                    "unexpected \"%c\"", ch);
//                 return NGX_ERROR;
//             }
//         }

//         if (last_space) {

//             start = b->pos - 1;
//             start_line = cf->conf_file->line;

//             if (ch == ' ' || ch == '\t' || ch == CR || ch == LF) {
//                 continue;
//             }

//             switch (ch) {

//             case ';':
//             case '{':
//                 if (cf->args->nelts == 0) {
//                     ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
//                                        "unexpected \"%c\"", ch);
//                     return NGX_ERROR;
//                 }

//                 if (ch == '{') {
//                     return NGX_CONF_BLOCK_START;
//                 }

//                 return NGX_OK;

//             case '}':
//                 if (cf->args->nelts != 0) {
//                     ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
//                                        "unexpected \"}\"");
//                     return NGX_ERROR;
//                 }

//                 return NGX_CONF_BLOCK_DONE;

//             case '#':
//                 sharp_comment = 1;
//                 continue;

//             case '\\':
//                 quoted = 1;
//                 last_space = 0;
//                 continue;

//             case '"':
//                 start++;
//                 d_quoted = 1;
//                 last_space = 0;
//                 continue;

//             case '\'':
//                 start++;
//                 s_quoted = 1;
//                 last_space = 0;
//                 continue;

//             case '$':
//                 variable = 1;
//                 last_space = 0;
//                 continue;

//             default:
//                 last_space = 0;
//             }

//         } else {
//             if (ch == '{' && variable) {
//                 continue;
//             }

//             variable = 0;

//             if (ch == '\\') {
//                 quoted = 1;
//                 continue;
//             }

//             if (ch == '$') {
//                 variable = 1;
//                 continue;
//             }

//             if (d_quoted) {
//                 if (ch == '"') {
//                     d_quoted = 0;
//                     need_space = 1;
//                     found = 1;
//                 }

//             } else if (s_quoted) {
//                 if (ch == '\'') {
//                     s_quoted = 0;
//                     need_space = 1;
//                     found = 1;
//                 }

//             } else if (ch == ' ' || ch == '\t' || ch == CR || ch == LF
//                        || ch == ';' || ch == '{')
//             {
//                 last_space = 1;
//                 found = 1;
//             }

//             if (found) {
//                 word = ngx_array_push(cf->args);
//                 if (word == NULL) {
//                     return NGX_ERROR;
//                 }

//                 word->data = ngx_pnalloc(cf->pool, b->pos - 1 - start + 1);
//                 if (word->data == NULL) {
//                     return NGX_ERROR;
//                 }

//                 for (dst = word->data, src = start, len = 0;
//                      src < b->pos - 1;
//                      len++)
//                 {
//                     if (*src == '\\') {
//                         switch (src[1]) {
//                         case '"':
//                         case '\'':
//                         case '\\':
//                             src++;
//                             break;

//                         case 't':
//                             *dst++ = '\t';
//                             src += 2;
//                             continue;

//                         case 'r':
//                             *dst++ = '\r';
//                             src += 2;
//                             continue;

//                         case 'n':
//                             *dst++ = '\n';
//                             src += 2;
//                             continue;
//                         }

//                     }
//                     *dst++ = *src++;
//                 }
//                 *dst = '\0';
//                 word->len = len;

//                 if (ch == ';') {
//                     return NGX_OK;
//                 }

//                 if (ch == '{') {
//                     return NGX_CONF_BLOCK_START;
//                 }

//                 found = 0;
//             }
//         }
//     }
// }