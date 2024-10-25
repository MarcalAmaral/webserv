#ifndef PARSER_VALIDATIONS_HPP
# define PARSER_VALIDATIONS_HPP

#include <stdexcept>

struct t_conf_file;

namespace master {
	namespace parser {
		namespace validation {
			void	validateFile(t_conf_file *conf);
		}
	}
}

#endif // PARSER_VALIDATIONS_HPP