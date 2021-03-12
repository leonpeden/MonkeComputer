#pragma once

#include <functional>
#include <string>
#include <vector>
#include "../EKeyboardKey.hpp"

namespace GorillaUI
{
    class UIOptionInputHandler
    {
        public:
            UIOptionInputHandler(GorillaUI::EKeyboardKey selectKey, bool canSelect);
            std::function<void(EKeyboardKey)> optionCallback = &nullopt;
            bool HandleKey(GorillaUI::EKeyboardKey key);

            EKeyboardKey currentOption = EKeyboardKey::Option1;
        private:
            const GorillaUI::EKeyboardKey _selectKey;
            const bool _canSelect;
            
            static void nullopt(EKeyboardKey) {};
    };
}