#pragma once
#include "EKeyboardKey.hpp"
#include <string>

namespace GorillaUI::KeyExtension
{
    bool NameToKey(std::string name, EKeyboardKey& out);
    bool IsFunctionKey(EKeyboardKey key);
    bool IsNumberKey(EKeyboardKey key);
    bool IsLetterKey(EKeyboardKey key);
    bool TryParseNumber(EKeyboardKey key, int& out);
    bool TryParseLetter(EKeyboardKey key, char& out);
}