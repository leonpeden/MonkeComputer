#pragma once
#include "ModEntry.hpp"
#include <vector>

namespace GorillaUI
{
    class Register
    {
        public:
            template<class T>
            static void RegisterModView(std::string name, std::string version) 
            {
                RegisterModView({name, version}, classof(T));
            }

            template<class T>
            static void RegisterModView(ModInfo info) 
            {
                RegisterModView(info, classof(T));
            }

            static std::vector<ModEntry>& get_entries()
            {
                return entries;
            }
            
        private:
            static inline std::vector<ModEntry> entries = {};
            static void RegisterModView(ModInfo info, Il2CppClass* klass);
            static void RegisterModView(std::string name, std::string version, Il2CppClass* klass);
    };
}