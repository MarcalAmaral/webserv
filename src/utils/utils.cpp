#include "Utils.hpp"
#include <cctype>

std::string Utils::trim(const std::string &str) {
    std::string subStr;
	size_t first = 0;
    size_t last = str.size();

    while (first < last && std::isspace(str[first])) {
        ++first;
    }
    while (last > first && std::isspace(str[last - 1])) {
        --last;
    }
    return (str.substr(first, last - first));
}
