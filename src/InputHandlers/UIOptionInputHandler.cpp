#include "InputHandlers/UIOptionInputHandler.hpp"

namespace GorillaUI
{
    UIOptionInputHandler::UIOptionInputHandler(GorillaUI::EKeyboardKey selectKey, bool canSelect) : _selectKey(selectKey), _canSelect(canSelect) {};

    bool UIOptionInputHandler::HandleKey(GorillaUI::EKeyboardKey key)
    {
        if (key == _selectKey && _canSelect)
        {
            optionCallback(currentOption);
            return true;
        }

        for (int i = (int) EKeyboardKey::Option1; i <= (int)EKeyboardKey::Option3; i++)
        {
            if (i == (int)key)
            {
                currentOption = key;
                return true;
            }
        }
        return false;
    }
}