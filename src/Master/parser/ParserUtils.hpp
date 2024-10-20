#ifndef PARSER_UTILS_HPP
# define PARSER_UTILS_HPP

# include <string>

namespace Master {
    namespace Parser {
        namespace Utils {
            std::string removeCommentsAndSpaces(const std::string &line);
        }
    }
}

#endif //PARSER_UTILS_HPP