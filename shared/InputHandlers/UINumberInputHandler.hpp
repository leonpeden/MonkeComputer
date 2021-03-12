#pragma once

#include <functional>
#include <string>
#include "../EKeyboardKey.hpp"

namespace GorillaUI
{
    class UINumberInputHandler
    {
        public:
            UINumberInputHandler(EKeyboardKey selectKey, bool canSelect);
            int number = 0;
            bool HandleKey(EKeyboardKey key);
            std::function<void(int)> numberCallback = &nullopt;
            int min = 0;
            int max = 0;
        private:
            const EKeyboardKey _selectKey;
            const bool _canSelect;
            std::string numberString = "";
            static void nullopt(int) {};

            void DeleteNum();
            void TypeNum(EKeyboardKey key);
            void UpdateNum();
    };
}