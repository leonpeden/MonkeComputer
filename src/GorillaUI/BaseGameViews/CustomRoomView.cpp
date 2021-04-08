#include "GorillaUI/BaseGameViews/CustomRoomView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "GorillaUI/BaseGameInterface.hpp"

#include "UnityEngine/Time.hpp"

DEFINE_TYPE(GorillaUI::CustomRoomView);

extern Logger& getLogger();

namespace GorillaUI
{
    void CustomRoomView::Awake()
    {
        if (!textInputHandler) textInputHandler = new UITextInputHandler(EKeyboardKey::Enter, true);
        if (!optionInputHandler) optionInputHandler = new UIOptionInputHandler(EKeyboardKey::Enter, false);
        lastUpdatedTime = UnityEngine::Time::get_time();
    }

    void CustomRoomView::DidActivate(bool firstActivation)
    {
        std::function<void(std::string)> fun = std::bind(&CustomRoomView::EnterCode, this, std::placeholders::_1);
        textInputHandler->textCallback = fun;
        textInputHandler->text = BaseGameInterface::Room::get_roomID();
        Redraw();
        lastUpdatedTime = UnityEngine::Time::get_time();
    }

    void CustomRoomView::Update()
    {
        float time = UnityEngine::Time::get_time();
        //bool connected = BaseGameInterface::Room::get_isConnectedToMaster();
        if (time > (lastUpdatedTime + 1.0f))// && connected)
        {
            Redraw();
            lastUpdatedTime = UnityEngine::Time::get_time();
        }
        /*
        else
        {
            getLogger().info("Time was: %.2f, last time was %.2f, connected to master was: %d", time, lastUpdatedTime, connected);
        }
        */
    }

    void CustomRoomView::EnterCode(std::string code)
    {
        BaseGameInterface::JoinRoom(code);
    }

    void CustomRoomView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawCode();

        CustomComputer::Redraw();
    }
    
    void CustomRoomView::DrawHeader()
    {
        text += "<color=#ffff00>== <color=#fdfdfd>Settings/Room</color> ==</color>\n";
    }
    
    void CustomRoomView::DrawCode()
    {
        text += "  <size=40>Press enter to join or create a room with the entered code</size>\n";
        text += string_format("  Your Entered room code:\n  <color=#fdfdfd>%s</color>\n\n", textInputHandler->text.c_str());
        text += "\n  <size=40>Press Option 1 to Disconnect from the current room</size>\n";
        char playerCount = BaseGameInterface::Room::get_playerCount();
        text += playerCount > 0 ? string_format("  Current Room: <color=#fdfdfd>%s</color>\n", BaseGameInterface::Room::get_roomID().c_str()) : "";
        text += playerCount > 0 ? string_format("  Players in room: <color=#fdfdfd>%d</color>", playerCount) : "  Not in a room";
        text += "\n";
        text += string_format("  Players online: <color=#fdfdfd>%d</color>", BaseGameInterface::Room::get_currentPlayers());
        text += "\n";
    }
    
    void CustomRoomView::OnKeyPressed(int key)
    {
        textInputHandler->HandleKey((EKeyboardKey)key);
        if (textInputHandler->text.size() > 10) textInputHandler->text = textInputHandler->text.substr(0, 10);

        if (optionInputHandler->HandleKey((EKeyboardKey)key))
        {
            if (optionInputHandler->currentOption == EKeyboardKey::Option1)
            {
                BaseGameInterface::Disconnect();
            }
        }
        Redraw();
    }
}