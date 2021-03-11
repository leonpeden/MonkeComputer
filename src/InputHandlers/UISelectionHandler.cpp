#include "InputHandlers/UISelectionHandler.hpp"

namespace GorillaUI
{
    UISelectionHandler::UISelectionHandler(GorillaUI::EKeyboardKey upKey, GorillaUI::EKeyboardKey downKey, GorillaUI::EKeyboardKey selectKey, bool canSelect) : _upKey(upKey), _downKey(downKey), _selectKey(selectKey), _canSelect(canSelect)
    {

    }

    bool UISelectionHandler::HandleKeyPress(GorillaUI::EKeyboardKey key)
    {
        if (key == _upKey)
        {
            MoveSelectionUp();
            return true;
        }

        if (key == _downKey)
        {
            MoveSelectionDown();
            return true;
        }

        if (_canSelect && key == _selectKey)
        {
            selectionCallback(currentSelectionIndex);
            return true;
        }

        return false;
    }

    void UISelectionHandler::MoveSelectionUp()
    {
        currentSelectionIndex--;
        ClampSelection();
    }

    void UISelectionHandler::MoveSelectionDown()
    {
        currentSelectionIndex++;
        ClampSelection();
    }

    void UISelectionHandler::ClampSelection()
    {
        if (currentSelectionIndex > max)
        {
            currentSelectionIndex = max;
            return;
        }

        if (currentSelectionIndex < min)
        {
            currentSelectionIndex = min;
        }
    }
}