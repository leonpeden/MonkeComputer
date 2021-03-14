#pragma once

#include <functional>
#include "../EKeyboardKey.hpp"

namespace GorillaUI
{
    class UIToggleInputHandler
    {
        public:
            bool state;
            UIToggleInputHandler(GorillaUI::EKeyboardKey toggleKey, GorillaUI::EKeyboardKey selectKey, bool canSelect);
            std::function<void(bool)> toggleCallback = &nullopt;
            bool HandleKey(EKeyboardKey key);

        private:
            const bool sameKey = false;
            const GorillaUI::EKeyboardKey _selectKey;
            const GorillaUI::EKeyboardKey _toggleKey;
            const bool _canSelect;
            static void nullopt(bool) {};
    };
}