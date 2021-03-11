#include "GorillaUI/MainView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/CustomComputer.hpp"

DEFINE_CLASS(GorillaUI::MainView);

extern Logger& getLogger();

namespace GorillaUI
{
    void MainView::Awake()
    {
        selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        selectionHandler->max = Register::get_entries().size() - 1;
        textInputHandler = new UITextInputHandler();
    }

    void MainView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&MainView::ShowModView, this, std::placeholders::_1);
        selectionHandler->selectionCallback = fun;
        
        if (firstActivation)
        {
            Redraw();

        }
    }

    void MainView::DidDeactivate()
    {
        getLogger().info("main View Was Deactivated!");
    }

    void MainView::ShowModView(int index)
    {
        std::vector<ModEntry>& entries = Register::get_entries();
        if (entries.size() == 0) return;
        ModEntry& entry = entries[selectionHandler->currentSelectionIndex];
        CustomComputer::instance->activeViewManager->ReplaceTopView(entry.get_view());
    }

    void MainView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawMods();

        text += textInputHandler->text;
        text += "\n";

        CustomComputer::instance->Redraw();
    }
    
    void MainView::DrawHeader()
    {
        text += "<color=#ffff00>===========================================</color>\n";
        text += "               <color=#00ff00>MonkeComputer</color>\n";
        text += "             <color=#ff0000>RedBrumbler</color> <color=#8800dd>Quest</color>\n";
        text += "<color=#ffff00>===========================================</color>\n";
    }
    
    void MainView::DrawMods()
    {
        const std::vector<ModEntry>& entries = Register::get_entries();
        int i = 0;
        for (auto& e : entries)
        {
            text += selectionHandler->currentSelectionIndex == i ? "<color=#ed6540>></color> " : "  ";
            text += e.get_info().id;
            text += "\n";
            i++;
        }
    }
    
    void MainView::OnKeyPressed(int key)
    {
        selectionHandler->HandleKeyPress((EKeyboardKey)key);
        textInputHandler->HandleKey((EKeyboardKey)key);
        Redraw();
    }
}