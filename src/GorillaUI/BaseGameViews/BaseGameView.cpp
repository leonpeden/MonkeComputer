#include "GorillaUI/BaseGameViews/BaseGameView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "GorillaUI/BaseGameViews/ColorChangeView.hpp"
#include "GorillaUI/BaseGameViews/NameChangeView.hpp"
#include "GorillaUI/BaseGameViews/TurnChangeView.hpp"
#include "GorillaUI/BaseGameViews/CustomRoomView.hpp"
#include "GorillaUI/BaseGameViews/GroupChangeView.hpp"
#include "GorillaUI/BaseGameViews/MicChangeView.hpp"
#include "GorillaUI/BaseGameViews/QueueChangeView.hpp"
#include "Helpers/SelectionHelper.hpp"
#include "GorillaUI/BaseGameInterface.hpp"

DEFINE_TYPE(GorillaUI::BaseGameView);

extern Logger& getLogger();

namespace GorillaUI
{
    void BaseGameView::Awake()
    {
        customRoomView = nullptr;
        nameChangeView = nullptr;
        colorChangeView = nullptr;
        turnChangeView = nullptr;
        micChangeView = nullptr;
        groupChangeView = nullptr;
        queueChangeView = nullptr;

        std::string gameVer = BaseGameInterface::get_gameVersion();
        if (gameVer == "live102") old = true; 
    	else if (gameVer == "live101") old = true;
        if (!selectionHandler) selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        selectionHandler->max = old ? 4 : 7;
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
                CustomComputer::get_instance()->activeViewManager->ReplaceTopView(customRoomView);
                break;
            case 1:
                if (!nameChangeView) nameChangeView = CreateView<NameChangeView*>();
                CustomComputer::get_instance()->activeViewManager->ReplaceTopView(nameChangeView);
                break;
            case 2:
                if (!colorChangeView) colorChangeView = CreateView<ColorChangeView*>();
                CustomComputer::get_instance()->activeViewManager->ReplaceTopView(colorChangeView);
                break;
            case 3:
                if (!turnChangeView) turnChangeView = CreateView<TurnChangeView*>();
                CustomComputer::get_instance()->activeViewManager->ReplaceTopView(turnChangeView);
                break;
            case 4:
                if (!micChangeView) micChangeView = CreateView<MicChangeView*>();
                CustomComputer::get_instance()->activeViewManager->ReplaceTopView(micChangeView);
                break;
            case 5:
                if (!groupChangeView) groupChangeView = CreateView<GroupChangeView*>();
                CustomComputer::get_instance()->activeViewManager->ReplaceTopView(groupChangeView);
                break;
            case 6:
                if (!queueChangeView) queueChangeView = CreateView<QueueChangeView*>();
                CustomComputer::get_instance()->activeViewManager->ReplaceTopView(queueChangeView);
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
        std::string gameVer = BaseGameInterface::get_gameVersion();
        text += string_format("<color=#ffff00>== <color=#fdfdfd>Settings</color> ==</color>\n", gameVer.c_str());
    }
    
    void BaseGameView::DrawViews()
    {
        text += " <size=40>Change the base game settings in this menu</size>\n";

        std::vector<std::string> views = {
                "Room Config",
                "Name Config",
                "Color Config",
                "Turn Config"
        };

        if (!old)
        {
            views.push_back("Mic Config");
            views.push_back("Group Config");
            views.push_back("Queue Config");
        }

        SelectionHelper::DrawSelection(views, selectionHandler->currentSelectionIndex, text);
    }
    
    void BaseGameView::OnKeyPressed(int key)
    {
        selectionHandler->HandleKey((EKeyboardKey)key);
        Redraw();
    }
}