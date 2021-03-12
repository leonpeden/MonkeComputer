#include "GorillaUI/MainView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/CustomComputer.hpp"

DEFINE_CLASS(GorillaUI::MainView);

extern Logger& getLogger();

#define MENU_OPTIONS 2

namespace GorillaUI
{
    void MainView::Awake()
    {
        selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        selectionHandler->max = MENU_OPTIONS;
    }

    void MainView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&MainView::ShowView, this, std::placeholders::_1);
        selectionHandler->selectionCallback = fun;
        
        if (firstActivation)
        {
            Redraw();
        }
    }

    void MainView::ShowView(int index)
    {
        switch(index)
        {
            case 0:
                if (!modSettingsViewManager) modSettingsViewManager = CreateViewManager<ModSettingsViewManager*>();
                CustomComputer::instance->activeViewManager->PresentViewManager(modSettingsViewManager);
                break;
            case 1:
                if (!baseGameViewManager) baseGameViewManager = CreateViewManager<BaseGameViewManager*>();
                CustomComputer::instance->activeViewManager->PresentViewManager(baseGameViewManager);
            default:
                getLogger().error("Selected view was out of range"); 
                break;
        }
    }

    void MainView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawSubMenus();

        CustomComputer::Redraw();
    }
    
    void MainView::DrawHeader()
    {
        text += "<color=#ffff00>===========================================</color>\n";
        text += "               <color=#00ff00>MonkeComputer</color>\n";
        text += "             <color=#ff0000>RedBrumbler</color> <color=#8800dd>Quest</color>\n";
        text += "<color=#ffff00>===========================================</color>\n";
    }
    
    void MainView::DrawSubMenus()
    {
        for (int i = 0; i < MENU_OPTIONS; i++)
        {
            text += selectionHandler->currentSelectionIndex == i ? "<color=#ed6540>></color> " : "  ";
            switch(i)
            {
                case 0:
                    text += "Mod Settings";
                    break;
                case 1:
                    text += "Base Game Settings";
                default:
                    break;
            }
            text += "\n";
        }
    }
    
    void MainView::OnKeyPressed(int key)
    {
        selectionHandler->HandleKey((EKeyboardKey)key);
        Redraw();
    }
}