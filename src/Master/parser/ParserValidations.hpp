#ifndef PARSER_VALIDATIONS_HPP
# define PARSER_VALIDATIONS_HPP

#include <stdexcept>

struct t_conf_file;

namespace Master {
	namespace Parser {
		namespace Validation {
			void	validateFile(t_conf_file *conf);
		}
	}
}

#endif // PARSER_VALIDATIONS_HPP