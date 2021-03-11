#pragma once

#include <string>
#include "EKeyboardKey.hpp"

namespace GorillaUI
{
    class UITextInputHandler
    {
        public:
            std::string text;
            bool HandleKey(EKeyboardKey key);

        private:
            void TypeChar(EKeyboardKey key);
            void AddSpace();
            void DeleteChar();
    };
}