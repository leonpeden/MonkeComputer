#include "Utils/TextUtils.hpp"

namespace TextUtils
{
    std::string toLower(std::string src)
    {
        std::string result = "";

        for (auto c : src)
        {
            result += tolower(c);
        }

        return result;
    }
}