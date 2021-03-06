#include "Components/Field.hpp"

DEFINE_CLASS(GorillaUI::Components::Field);

extern Logger& getLogger();

namespace GorillaUI::Components
{
    void Field::HandleInput(Il2CppString* input)
    {
        std::string val = to_utf8(csstrtostr(input));
        getLogger().info("Input '%s' was given!", val.c_str());
    }
}