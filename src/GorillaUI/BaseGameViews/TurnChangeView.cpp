#include "GorillaUI/BaseGameViews/TurnChangeView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "GorillaUI/BaseGameInterface.hpp"
#include "Helpers/SelectionHelper.hpp"

DEFINE_CLASS(GorillaUI::TurnChangeView);

extern Logger& getLogger();

namespace GorillaUI
{
    void TurnChangeView::Awake()
    {
        if (!selectionHandler) selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        selectionHandler->max = 3;

        if (!turnValueHandler) turnValueHandler = new UISelectionHandler(EKeyboardKey::Left, EKeyboardKey::Right, EKeyboardKey::Enter, false);
        turnValueHandler->min = 0;
        turnValueHandler->max = 10;

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
        if (BaseGameInterface::SnapTurn::get_turnType() == turnType && turnValue == BaseGameInterface::SnapTurn::get_turnValue()) return;

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
        text += "<color=#ffff00>== <color=#fdfdfd>Turn Config</color> ==</color>\n";
    }
    
    void TurnChangeView::DrawTurn()
    {
        text += "<size=40>  Change your turning type here, the options speak for themselves\n  use up and down to select type,\n  use left and right to select speed\n</size>";
        std::vector<std::string> types = {
            "Snap turning",
            "Smooth turning",
            "None"
        };

        SelectionHelper::DrawSelection(types, selectionHandler->currentSelectionIndex, text);

        text += "\n";
        text += string_format("  Turn Speed: <color=#adbdad>< <color=#fdfdfd>%d</color> ></color>\n", turnValueHandler->currentSelectionIndex);
    }
    
    void TurnChangeView::OnKeyPressed(int key)
    {
        selectionHandler->HandleKey((EKeyboardKey)key);
        turnValueHandler->HandleKey((EKeyboardKey)key);
        Redraw();
    }
}