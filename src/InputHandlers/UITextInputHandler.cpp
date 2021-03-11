#include "InputHandlers/UITextInputHandler.hpp"
#include "KeyExtension.hpp"
#include "beatsaber-hook/shared/utils/utils.h"

using namespace GorillaUI::KeyExtension;

extern Logger& getLogger();

namespace GorillaUI
{
    bool UITextInputHandler::HandleKey(EKeyboardKey key)
    {
        if (key == EKeyboardKey::Delete)
        {
            DeleteChar();
            return true;
        }

        if (key == EKeyboardKey::Space)
        {
            AddSpace();
            return true;
        }

        if (IsFunctionKey(key)) 
        {
            return false;
        }
        TypeChar(key);
        return true;
    }

    void UITextInputHandler::TypeChar(EKeyboardKey key)
    {
        int num;
        if (TryParseNumber(key, num))
        {
            text += string_format("%d", num);
            return;
        }

        char letter;
        TryParseLetter(key, letter);
        text += string_format("%c", letter);
    }

    void UITextInputHandler::AddSpace()
    {
        text += " ";
    }

    void UITextInputHandler::DeleteChar()
    {
        int length = text.length();
        if(length == 0) return;
        text = text.substr(0, length - 1);
    }
}