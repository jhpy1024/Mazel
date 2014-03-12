#include <sstream>

namespace util
{
    template <typename T>
    T stringToNum(const std::string& str)
    {
        std::stringstream ss(str);

        T result;
        ss >> result;

        return result;
    }

    template <typename T>
    std::string toString(T var)
    {
        std::stringstream ss;

        ss << var;

        return ss.str();
    }
}
