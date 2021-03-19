#include "InputHandlers/UISelectionHandler.hpp"

namespace GorillaUI
{
    UISelectionHandler::UISelectionHandler(GorillaUI::EKeyboardKey upKey, GorillaUI::EKeyboardKey downKey, GorillaUI::EKeyboardKey selectKey, bool canSelect, bool wrapAround) : _upKey(upKey), _downKey(downKey), _selectKey(selectKey), _canSelect(canSelect), _wrapAround(wrapAround) {};

    bool UISelectionHandler::HandleKey(GorillaUI::EKeyboardKey key)
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
        if (currentSelectionIndex >= max && !_wrapAround)
        {
            currentSelectionIndex = max - 1;
            return;
        }
        else if (currentSelectionIndex >= max)
        {
            currentSelectionIndex = min;
            return;
        }

        if (currentSelectionIndex < min && !_wrapAround)
        {
            currentSelectionIndex = min;
        }
        else if (currentSelectionIndex < min)
        {
            currentSelectionIndex = max - 1;
        }
    }
}