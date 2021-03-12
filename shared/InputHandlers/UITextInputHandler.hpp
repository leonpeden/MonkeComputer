#pragma once

#include <functional>
#include <string>
#include "../EKeyboardKey.hpp"

namespace GorillaUI
{
    class UITextInputHandler
    {
        public:
            std::string text;
            UITextInputHandler(GorillaUI::EKeyboardKey selectKey, bool canSelect);
            std::function<void(std::string)> textCallback = &nullopt;
            bool HandleKey(EKeyboardKey key);

        private:
            const GorillaUI::EKeyboardKey _selectKey;
            const bool _canSelect;
            void TypeChar(EKeyboardKey key);
            void AddSpace();
            void DeleteChar();
            static void nullopt(std::string) {};
    };
}