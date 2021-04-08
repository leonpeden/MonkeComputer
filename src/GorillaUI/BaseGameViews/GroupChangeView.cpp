#include "GorillaUI/BaseGameViews/GroupChangeView.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "Helpers/SelectionHelper.hpp"
#include "GorillaUI/BaseGameInterface.hpp"

DEFINE_TYPE(GorillaUI::GroupChangeView);

extern Logger& getLogger();

namespace GorillaUI
{
    void GroupChangeView::Awake()
    {
        counter = 0;
        if (!selectionHandler) selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        selectionHandler->max = 2;

        std::string group = BaseGameInterface::Group::get_group();
        selectionHandler->currentSelectionIndex = BaseGameInterface::Group::groupToIndex(group);
    }
    
    void GroupChangeView::Update()
    {
        counter ++;
        if (counter > 200)
        {
            counter = 0;
            Redraw();
            getLogger().info("Redrawing screen!");
        }
    }

    void GroupChangeView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&GroupChangeView::ChangeGroup, this, std::placeholders::_1);
        selectionHandler->selectionCallback = fun;
        Redraw();
    }

    void GroupChangeView::ChangeGroup(int index)
    {
        std::string type = "";
        switch(index)
        {
            case 0:
                type = "FOREST";
                break;
            case 1:
                type = "CAVE";
                break;
            default:
                break;
        }

        BaseGameInterface::SetGroup(type);
    }

    void GroupChangeView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawGroups();

        CustomComputer::Redraw();
    }
    
    void GroupChangeView::DrawHeader()
    {
        text += "<color=#ffff00>== <color=#fdfdfd>Settings/Group</color> ==</color>\n";
    }
    
    void GroupChangeView::DrawGroups()
    {
        text += string_format(" <size=40>Change The Group settings in this menu\n  Press enter to confirm your choice\n  Current players close enough: <color=#fdfdfd>%d</color>\n</size>", BaseGameInterface::Room::get_collidingPlayers());

        std::vector<std::string> groups = {
            "Forest",
            "Cave"
        };
        
        SelectionHelper::DrawSelection(groups, selectionHandler->currentSelectionIndex, text);
        text += "\n<size=40> Use this to join a public room with a group of friends.\n";
        text += "  1) Get everyone into a private room\n";
        text += "  2) Go to this tab\n";
        text += "  3) Make sure everyone is close to the computer\n";
        text += "  4) Select a map to group join (up/down)\n";
        text += "  5) Press Enter\n</size>";
    }
    
    void GroupChangeView::OnKeyPressed(int key)
    {
        selectionHandler->HandleKey((EKeyboardKey)key);
        Redraw();
    }
}