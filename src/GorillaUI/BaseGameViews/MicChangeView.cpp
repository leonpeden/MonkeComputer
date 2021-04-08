#include "GorillaUI/BaseGameViews/MicChangeView.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "Helpers/SelectionHelper.hpp"
#include "GorillaUI/BaseGameInterface.hpp"

DEFINE_TYPE(GorillaUI::MicChangeView);

extern Logger& getLogger();

namespace GorillaUI
{
    void MicChangeView::Awake()
    {
        if (!selectionHandler) selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        selectionHandler->max = 3;

        std::string pttType = BaseGameInterface::Mic::get_pttType();
        selectionHandler->currentSelectionIndex = BaseGameInterface::Mic::pttTypeToIndex(pttType);
    }

    void MicChangeView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&MicChangeView::ChangeMic, this, std::placeholders::_1);
        selectionHandler->selectionCallback = fun;
        Redraw();
    }

    void MicChangeView::ChangeMic(int index)
    {
        std::string type = "";
        switch(index)
        {
            case 0:
                type = "ALL CHAT";
                break;
            case 1:
                type = "PUSH TO TALK";
                break;
            case 2:
                type = "PUSH TO MUTE";
                break;
            default:
                break;
        }

        BaseGameInterface::SetpttType(type);
    }

    void MicChangeView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawMic();

        CustomComputer::Redraw();
    }
    
    void MicChangeView::DrawHeader()
    {
        text += "<color=#ffff00>== <color=#fdfdfd>Settings/Mic</color> ==</color>\n";
    }
    
    void MicChangeView::DrawMic()
    {
        text += string_format(" <size=40>Change The Mic settings in this menu\n  Press enter to confirm your choice\n</size> Current Setting: <color=#fdfdfd>%s</color>\n", BaseGameInterface::Mic::get_pttType().c_str());

        std::vector<std::string> micOptions = {
            "All chat",
            "Push to Talk",
            "Push To Mute",
        };
        
        SelectionHelper::DrawSelection(micOptions, selectionHandler->currentSelectionIndex, text);

        switch (selectionHandler->currentSelectionIndex)
        {
            case 0:
                break;
            case 1:
                text += "<size=40>\n  Use any of the face buttons (A/B/X/Y) to unmute\n</size>";
                break;
            case 2:
                text += "<size=40>\n  Use any of the face buttons (A/B/X/Y) to mute\n</size>";
                break;
            default:
                break;
        }
    }
    
    void MicChangeView::OnKeyPressed(int key)
    {
        selectionHandler->HandleKey((EKeyboardKey)key);
        Redraw();
    }
}