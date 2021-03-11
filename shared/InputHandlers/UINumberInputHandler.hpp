#pragma once

#include "EKeyboardKey.hpp"

namespace GorillaUI
{
    class UINumberInputHandler
    {
        public:
            int number = 0;
            bool HandleKey(EKeyboardKey key);
    };
}