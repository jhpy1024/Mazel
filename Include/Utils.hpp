#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

namespace util
{
    template <typename T>
    T stringToNum(const std::string& str);

    template <typename T>
    std::string toString(T var);
}

#include "Utils.inl"

#endif // UTILS_HPP
