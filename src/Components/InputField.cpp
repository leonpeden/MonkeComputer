#include "Components/InputField.hpp"

DEFINE_CLASS(GorillaUI::Components::InputField);

extern Logger& getLogger();

namespace GorillaUI::Components
{
    void InputField::Backspace()
    {
        getLogger().info("Backspace was pressed!");
    }

    void InputField::Option1()
    {
        getLogger().info("Option 1 was pressed!");
    }

    void InputField::Option2()
    {
        getLogger().info("Option 2 was pressed!");
    }

    void InputField::Option3()
    {
        getLogger().info("Option 3 was pressed!");
    }

    void InputField::Enter()
    {
        getLogger().info("Enter was pressed!");
    }

    void InputField::HandleInput(Il2CppString* input)
    {
        std::string val = to_utf8(csstrtostr(input));
        getLogger().info("Character input '%s' was given!", val.c_str());
    }
}