#ifndef PARSER_UTILS_HPP
# define PARSER_UTILS_HPP

# include <string>

namespace master {
    namespace parser {
        namespace utils {
            std::string remove_comments_spaces(const std::string &line);
            // void adjustBracketsLeft(std::string &fline);
        }
    }
}

#endif //PARSER_UTILS_HPP