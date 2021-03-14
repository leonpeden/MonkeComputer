#include "InputHandlers/UIToggleInputHandler.hpp"

namespace GorillaUI
{
    UIToggleInputHandler::UIToggleInputHandler(GorillaUI::EKeyboardKey toggleKey, EKeyboardKey selectKey, bool canSelect) : _toggleKey(toggleKey), _selectKey(selectKey), _canSelect(canSelect), sameKey(toggleKey == selectKey) {};

    bool UIToggleInputHandler::HandleKey(EKeyboardKey key)
    {
        if (sameKey) // if both toggle and select are the same key, the check can be simplified
        {
            if (key == _toggleKey)
            {
                state = !state;
                toggleCallback(state);
                return true;
            }
        }
        else // if they are not the same key, the check is seperated and handled differently
        {
            if (key == _toggleKey)
            {
                state = !state;
                return true;
            }

            if (key == _selectKey && _canSelect)
            {
                toggleCallback(state);
                return true;
            }
        }
        return false; // invalid key for this handler
    }
}