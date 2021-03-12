#include "GorillaUI/BaseGameViews/TurnChangeView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "GorillaUI/BaseGameInterface.hpp"

DEFINE_CLASS(GorillaUI::TurnChangeView);

extern Logger& getLogger();

namespace GorillaUI
{
    void TurnChangeView::Awake()
    {
        if (!selectionHandler) selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        selectionHandler->max = 2;

        if (!turnValueHandler) turnValueHandler = new UISelectionHandler(EKeyboardKey::Left, EKeyboardKey::Right, EKeyboardKey::Enter, false);
        turnValueHandler->min = 0;
        turnValueHandler->max = 9;

        std::string turnType = BaseGameInterface::SnapTurn::get_turnType();

        selectionHandler->currentSelectionIndex = BaseGameInterface::SnapTurn::turnTypeToIndex(turnType);
        turnValueHandler->currentSelectionIndex = BaseGameInterface::SnapTurn::get_turnValue();
    }

    void TurnChangeView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&TurnChangeView::UpdateTurn, this, std::placeholders::_1);
        selectionHandler->selectionCallback = fun;
        
        if (firstActivation)
        {
            Redraw();
        }
    }

    void TurnChangeView::UpdateTurn(int num)
    {
        int turnValue = turnValueHandler->currentSelectionIndex;
        std::string turnType = "";
        switch(selectionHandler->currentSelectionIndex)
        {
            case 0:
                turnType = "SNAP";
                break;
            case 1:
                turnType = "SMOOTH";
                break;
            case 2:
                turnType = "NONE";
                break;
            default:
                break;
        }

        BaseGameInterface::ChangeTurnMode(turnType, turnValue);
    }

    void TurnChangeView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawTurn();

        CustomComputer::Redraw();
    }
    
    void TurnChangeView::DrawHeader()
    {
        text += "<color=#ffff00>== <color=#fdfdfd>Color Config</color> ==</color>\n";
    }
    
    void TurnChangeView::DrawTurn()
    {
        for (int i = 0; i < 3; i++)
        {
            text += "\n";
            text += selectionHandler->currentSelectionIndex == i ? "<color=#ed6540>></color> " : "  ";
            switch(i)
            {
                case 0:
                    text += "SNAP";
                    break;
                case 1:
                    text += "SMOOTH";
                    break;
                case 2:
                    text += "NONE";
                    break;
                default:
                    break;
            }
            text += "\n";
        }
        text += "\n";
        text += string_format("  Turn Speed: <color=#adbdad><</color> %d <color=#adbdad>></color>\n", turnValueHandler->currentSelectionIndex);
    }
    
    void TurnChangeView::OnKeyPressed(int key)
    {
        selectionHandler->HandleKeyPress((EKeyboardKey)key);
        turnValueHandler->HandleKeyPress((EKeyboardKey)key);
        Redraw();
    }
}