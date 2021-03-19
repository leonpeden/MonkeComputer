#include "GorillaUI/MainView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "Helpers/SelectionHelper.hpp"
DEFINE_CLASS(GorillaUI::MainView);

extern Logger& getLogger();

#define MENU_OPTIONS 3

namespace GorillaUI
{
    void MainView::Awake()
    {
        selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        selectionHandler->max = MENU_OPTIONS;
        screenSaver = true;
    }

    void MainView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&MainView::ShowView, this, std::placeholders::_1);
        selectionHandler->selectionCallback = fun;
        
        if (!firstActivation)
            Redraw();
    }

    void MainView::ShowView(int index)
    {
        switch(index)
        {
            case 0:
                if (!baseGameViewManager) baseGameViewManager = CreateViewManager<BaseGameViewManager*>();
                CustomComputer::get_instance()->activeViewManager->PresentViewManager(baseGameViewManager);
                break;
            case 1:
                if (!modSettingsViewManager) modSettingsViewManager = CreateViewManager<ModSettingsViewManager*>();
                CustomComputer::get_instance()->activeViewManager->PresentViewManager(modSettingsViewManager);
                break;
            case 2:
                if (!detailView) detailView = CreateView<DetailView*>();
                CustomComputer::get_instance()->activeViewManager->ReplaceTopView(detailView);
                break;
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
        text += "              by: <color=#ff0000>RedBrumbler</color>\n";
        text += "<color=#ffff00>===========================================</color>\n";
    }
    
    void MainView::DrawSubMenus()
    {
        std::vector<std::string> options = {
            "Game Settings",
            "Mod Settings",
            "Details"
        };

        SelectionHelper::DrawSelection(options, selectionHandler->currentSelectionIndex, text);
    }
    
    void MainView::OnKeyPressed(int key)
    {
        if (!screenSaver)
        {
            selectionHandler->HandleKey((EKeyboardKey)key);
        }
        else screenSaver = false;
        Redraw();
    }
}