#include "GorillaUI/BaseGameViews/BaseGameView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "GorillaUI/BaseGameViews/ColorChangeView.hpp"
#include "GorillaUI/BaseGameViews/NameChangeView.hpp"
#include "GorillaUI/BaseGameViews/TurnChangeView.hpp"
#include "GorillaUI/BaseGameViews/CustomRoomView.hpp"

DEFINE_CLASS(GorillaUI::BaseGameView);

extern Logger& getLogger();

namespace GorillaUI
{
    void BaseGameView::Awake()
    {
        if (!selectionHandler) selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        selectionHandler->max = 3;

        customRoomView = nullptr;
        nameChangeView = nullptr;
        colorChangeView = nullptr;
        turnChangeView = nullptr;
    }

    void BaseGameView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&BaseGameView::ShowView, this, std::placeholders::_1);
        selectionHandler->selectionCallback = fun;
        
        if (firstActivation)
        {
            Redraw();
        }
    }

    void BaseGameView::ShowView(int index)
    {
        switch(index)
        {
            case 0:
                if (!customRoomView) customRoomView = CreateView<CustomRoomView*>();
                CustomComputer::instance->activeViewManager->ReplaceTopView(customRoomView);
                break;
            case 1:
                if (!nameChangeView) nameChangeView = CreateView<NameChangeView*>();
                CustomComputer::instance->activeViewManager->ReplaceTopView(nameChangeView);
                break;
            case 2:
                if (!colorChangeView) colorChangeView = CreateView<ColorChangeView*>();
                CustomComputer::instance->activeViewManager->ReplaceTopView(colorChangeView);
                break;
            case 3:
                if (!turnChangeView) turnChangeView = CreateView<TurnChangeView*>();
                CustomComputer::instance->activeViewManager->ReplaceTopView(turnChangeView);
                break;
            default:
                break;
        }
    }

    void BaseGameView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawViews();

        CustomComputer::Redraw();
    }
    
    void BaseGameView::DrawHeader()
    {
        text += "<color=#ffff00>== <color=#fdfdfd>Gorilla Tag Settings</color> ==</color>\n";
    }
    
    void BaseGameView::DrawViews()
    {
        for (int i = 0; i < 4; i++)
        {
            text += selectionHandler->currentSelectionIndex == i ? "<color=#ed6540>></color> " : "  ";
            switch(i)
            {
                case 0:
                    text += "Room Config";
                    break;
                case 1:
                    text += "Name Config";
                    break;
                case 2:
                    text += "Color Config";
                    break;
                case 3:
                    text += "Turn Config";
                    break;
                default:
                    break;
            }
            text += "\n";
        }
    }
    
    void BaseGameView::OnKeyPressed(int key)
    {
        selectionHandler->HandleKeyPress((EKeyboardKey)key);
        Redraw();
    }
}