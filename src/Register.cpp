#include "Register.hpp"

namespace GorillaUI
{
    void Register::RegisterModView(ModInfo info, Il2CppClass* klass)
    {
        entries.push_back(ModEntry(info, klass));
    }

    void Register::RegisterModView(std::string name, std::string version, Il2CppClass* klass)
    {
        entries.push_back(ModEntry({name, version}, klass));
    }
}