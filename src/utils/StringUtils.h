#ifndef GOOGLE_HASH_CODE_2022_C___STRINGUTILS_H
#define GOOGLE_HASH_CODE_2022_C___STRINGUTILS_H

#include <string>
#include <sstream>
#include <vector>
#include <iterator>

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

#endif //GOOGLE_HASH_CODE_2022_C___STRINGUTILS_H
