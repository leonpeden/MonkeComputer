#include "InputHandlers/UINumberInputHandler.hpp"
#include "KeyExtension.hpp"
#include "beatsaber-hook/shared/utils/utils.h"
using namespace GorillaUI::KeyExtension;

namespace GorillaUI
{
    UINumberInputHandler::UINumberInputHandler(EKeyboardKey selectKey, bool canSelect) : _selectKey(selectKey), _canSelect(canSelect) {};

    bool UINumberInputHandler::HandleKey(EKeyboardKey key)
    {
        if (key == EKeyboardKey::Delete)
        {
            DeleteNum();
            return true;
        }

        if (key == _selectKey && _canSelect)
        {
            numberCallback(number);
            return true;
        }

        if (!IsNumberKey(key)) return false;
        
        TypeNum(key);
        return true;
    }

    void UINumberInputHandler::DeleteNum()
    {
        numberString = "";
        UpdateNum();
    }

    void UINumberInputHandler::TypeNum(EKeyboardKey key)
    {
        int num;
        TryParseNumber(key, num);

        numberString += string_format("%d", num);
        UpdateNum();
    }

    void UINumberInputHandler::UpdateNum()
    {
        number = 0;
        for (auto c : numberString)
        {
            number *= 10;
            number += (int)(c - '0');
        }
    }
}