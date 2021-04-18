#pragma once

#include <string>
#include <vector>

class BackgroundsList
{
    public:
        static void Load();
        static std::vector<std::string>& get_list();
        static std::string get_fileName(int index);
    private:
        static inline std::vector<std::string> backgrounds = {};
};