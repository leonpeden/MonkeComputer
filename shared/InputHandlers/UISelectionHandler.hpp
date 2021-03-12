#pragma once

#include <functional>
#include <string>
#include <vector>
#include "../EKeyboardKey.hpp"

namespace GorillaUI
{
    class UISelectionHandler
    {
        public:
            UISelectionHandler(GorillaUI::EKeyboardKey upKey, GorillaUI::EKeyboardKey downKey, GorillaUI::EKeyboardKey selectKey, bool canSelect);
            std::function<void(int)> selectionCallback = &nullopt;
            int min = 0;
            int max = 0;
            int currentSelectionIndex = 0;
            bool HandleKeyPress(GorillaUI::EKeyboardKey key);

        private:
            const GorillaUI::EKeyboardKey _upKey;
            const GorillaUI::EKeyboardKey _downKey;
            const GorillaUI::EKeyboardKey _selectKey;
            const bool _canSelect;
            void MoveSelectionUp();
            void MoveSelectionDown();
            void ClampSelection();
            static void nullopt(int) {};
    };
}