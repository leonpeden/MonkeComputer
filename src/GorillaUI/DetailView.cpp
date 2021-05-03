#include "GorillaUI/DetailView.hpp"
#include "GorillaUI.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "GorillaUI/BaseGameInterface.hpp"
#include "BanManager.hpp"
#include "UnityEngine/Color.hpp"
#include "ViewLib/CustomScreenInfo.hpp"


DEFINE_TYPE(GorillaUI::DetailView);

extern Logger& getLogger();

namespace GorillaUI
{
    void DetailView::DidActivate(bool firstActivation)
    {
        Redraw();
    }

    void DetailView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawDetails();

        CustomComputer::Redraw();
    }
    
    void DetailView::DrawHeader()
    {
        text += "<color=#ffff00>== <color=#fdfdfd>Details</color> ==</color>\n";
    }
    
    void DetailView::DrawDetails()
    {
        // if user is banned
        if (BanManager::get_isBanned())
        {
            text += BanManager::get_displayMessage();
        }
        // if user is not banned
        else
        {
            text += "<size=40>  Refresh by reopening this menu\n</size>\n";
            text += " Current Game Version: <color=#fdfdfd>" + BaseGameInterface::get_gameVersion() + "</color>\n";
            text += " Current Name: <color=#fdfdfd>" + BaseGameInterface::Name::get_name() + "</color>\n\n";

            char playerCount = BaseGameInterface::Room::get_playerCount();
            if (playerCount > 0)
            {
                std::string room = BaseGameInterface::Room::get_roomID();
                text += " Current Room: <color=#fdfdfd>" + room + "</color>\n";
                text += string_format(" Players In Room: <color=#fdfdfd>%d</color>\n", playerCount);
            }
            else
            {
                text += " Not in Room\n";
            }

            text += string_format(" Players Online: <color=#fdfdfd>%d</color>\n", BaseGameInterface::Room::get_currentPlayers());
            int banned = BaseGameInterface::Room::get_bannedPlayers();
            if (banned >= 0)
                text += string_format(" Users banned yesterday: <color=#fdfdfd>%d</color>\n", banned);
        }
    }
}