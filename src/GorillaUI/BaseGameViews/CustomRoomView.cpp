#include "GorillaUI/BaseGameViews/CustomRoomView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "GorillaUI/BaseGameInterface.hpp"

DEFINE_CLASS(GorillaUI::CustomRoomView);

extern Logger& getLogger();

namespace GorillaUI
{
    void CustomRoomView::Awake()
    {
        if (!textInputHandler) textInputHandler = new UITextInputHandler(EKeyboardKey::Enter, true);
    }

    void CustomRoomView::DidActivate(bool firstActivation)
    {
        std::function<void(std::string)> fun = std::bind(&CustomRoomView::EnterCode, this, std::placeholders::_1);
        textInputHandler->textCallback = fun;
        textInputHandler->text = BaseGameInterface::Room::get_roomID();
        
        if (firstActivation)
        {
            Redraw();
        }
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
        text += "<color=#ffff00>== <color=#fdfdfd>Room Config</color> ==</color>\n";
    }
    
    void CustomRoomView::DrawCode()
    {
        text += "\n";
        text += string_format("  Your inputted room code: %s", textInputHandler->text.c_str());
    }
    
    void CustomRoomView::OnKeyPressed(int key)
    {
        textInputHandler->HandleKey((EKeyboardKey)key);
        if (textInputHandler->text.size() > 12) textInputHandler->text = textInputHandler->text.substr(0, 12);
        Redraw();
    }
}