#include "GorillaUI/BaseGameViews/VoiceChatView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "GorillaUI/BaseGameInterface.hpp"
#include "Helpers/SelectionHelper.hpp"

DEFINE_TYPE(GorillaUI::VoiceChatView);

extern Logger& getLogger();

namespace GorillaUI
{
    void VoiceChatView::Awake()
    {
        toggleInputHandler = new UIToggleInputHandler(EKeyboardKey::Option1, EKeyboardKey::Option1, true);

        toggleInputHandler->state = BaseGameInterface::Voice::get_voiceChat();
    }

    void VoiceChatView::DidActivate(bool firstActivation)
    {
        std::function<void(bool)> fun = std::bind(&VoiceChatView::UpdateVC, this, std::placeholders::_1);
        toggleInputHandler->toggleCallback = fun;
        
        if (firstActivation)
        {
            Redraw();
        }
    }

    void VoiceChatView::UpdateVC(bool value)
    {
        if (BaseGameInterface::Voice::get_voiceChat() ^ value)
            BaseGameInterface::SetVoiceChat(value);
    }

    void VoiceChatView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawVC();

        CustomComputer::Redraw();
    }
    
    void VoiceChatView::DrawHeader()
    {
        text += "<color=#ffff00>== <color=#fdfdfd>Settings/Voice</color> ==</color>\n";
    }
    
    void VoiceChatView::DrawVC()
    {
        text += "\n";

        bool enabled = BaseGameInterface::Voice::get_voiceChat();
        text += string_format("  Voice Chat is: <color=#%s>%s</color>", enabled ? "00fd00" : "fd0000", enabled ? "enabled" : "disabled");
        text += "<size=40>\n";
        text += "    To toggle voice chat enabled, press <color=#fdfdfd>Option 1</color>\n";
        text += "    When Voice chat is disabled, no one will hear you, and you will hear no one!";
        text += "\n</size>";
    }
    
    void VoiceChatView::OnKeyPressed(int key)
    {
        toggleInputHandler->HandleKey((EKeyboardKey)key);
        Redraw();
    }
}