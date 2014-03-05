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
}
