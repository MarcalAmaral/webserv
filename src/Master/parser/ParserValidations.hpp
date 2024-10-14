#ifndef PARSER_VALIDATIONS_HPP
# define PARSER_VALIDATIONS_HPP

#include <stdexcept>

# define ERROR -1

namespace Master {
	namespace Parser {
		namespace Validation {
			class	InvalidFileException : public std::exception {
				public:
					const char *what() const throw() {
						return ("Error Master Parser: invalid configuration file");
					}
			};
			void	validateFile(const char *pathname);
		}
	}
}

#endif // PARSER_VALIDATIONS_HPP