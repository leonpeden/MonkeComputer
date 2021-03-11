#include "Test/TestView.hpp"
#include "ViewLib/CustomComputer.hpp"
DEFINE_CLASS(GorillaUI::TestView);

extern Logger& getLogger();

namespace GorillaUI
{
    void TestView::Awake()
    {
        selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        selectionHandler->max = 4;
        activatedBefore = false;
    }

    void TestView::DidActivate(bool firstActivation)
    {
        if(firstActivation)
        {
            Redraw();
            getLogger().info("Test View says hi");
        }
        
    }

    void TestView::Redraw()
    {
        getLogger().info("Redrawing test view");
        text = "";

        text += "<color=#ffff00>==</color> TestView v1.0.0\n";

        for (int i = 0; i < 5; i++)
        {
            text += (i == selectionHandler->currentSelectionIndex ? "<color=#ed6540>></color> " : "  ");
            text += string_format("Option %d\n", i);
        }

        CustomComputer::instance->Redraw();
    }

    void TestView::OnKeyPressed(int key)
    {
        selectionHandler->HandleKeyPress((EKeyboardKey)key);
        Redraw();
    }
}