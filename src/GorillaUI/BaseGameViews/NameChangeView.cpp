#include "GorillaUI/BaseGameViews/NameChangeView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "GorillaUI/BaseGameInterface.hpp"

DEFINE_CLASS(GorillaUI::NameChangeView);

extern Logger& getLogger();

namespace GorillaUI
{
    void NameChangeView::Awake()
    {
        if (!textInputHandler) textInputHandler = new UITextInputHandler(EKeyboardKey::Enter, true);
        textInputHandler->text = BaseGameInterface::Name::get_name();
    }

    void NameChangeView::DidActivate(bool firstActivation)
    {
        std::function<void(std::string)> fun = std::bind(&NameChangeView::EnterName, this, std::placeholders::_1);
        textInputHandler->textCallback = fun;
        
        if (firstActivation)
        {
            Redraw();
        }
    }

    void NameChangeView::EnterName(std::string code)
    {
        BaseGameInterface::SetName(code);
    }

    void NameChangeView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawName();

        CustomComputer::Redraw();
    }
    
    void NameChangeView::DrawHeader()
    {
        text += "<color=#ffff00>== <color=#fdfdfd>Name Config</color> ==</color>\n";
    }
    
    void NameChangeView::DrawName()
    {
        text += "\n";
        text += "  <size=40>Press enter to change your name:</size>\n";
        text += string_format("  Your entered name:\n  <color=#fdfdfd>%s</color>\n", textInputHandler->text.c_str());
    }
    
    void NameChangeView::OnKeyPressed(int key)
    {
        textInputHandler->HandleKey((EKeyboardKey)key);
        if (textInputHandler->text.size() > 10) textInputHandler->text = textInputHandler->text.substr(0, 10);
        Redraw();
    }
}