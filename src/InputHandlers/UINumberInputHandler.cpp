#include "InputHandlers/UINumberInputHandler.hpp"
#include "KeyExtension.hpp"

using namespace GorillaUI::KeyExtension;

namespace GorillaUI
{
    bool UINumberInputHandler::HandleKey(EKeyboardKey key)
    {
        if (!IsNumberKey(key)) return false;
        TryParseNumber(key, number);
        return true;
    }
}