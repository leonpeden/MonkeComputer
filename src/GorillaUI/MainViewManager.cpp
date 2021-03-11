#include "GorillaUI/MainViewManager.hpp"
#include "GorillaUI/MainView.hpp"
#include "GorillaUI.hpp"
#include "beatsaber-hook/shared/utils/utils.h"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

DEFINE_CLASS(GorillaUI::MainViewManager);

using namespace GorillaUI::Components;

extern Logger& getLogger();

namespace GorillaUI
{
    
    void MainViewManager::DidActivate(bool firstActivation)
    {
        if (firstActivation)
        {
            
            getLogger().info("Main View Manager says hello!");
        }
    }

    void MainViewManager::NotifyOfKeyPress(int key)
    {
        if (key == (int)EKeyboardKey::Back)
        {
            il2cpp_utils::RunMethod(this, "BackButtonWasPressed", activeView);
        }
        else
        {
            if (activeView) 
            {
                getLogger().info("ran onkeypressed on view");
                il2cpp_utils::RunMethod(activeView, "OnKeyPressed", key);
            }
            else getLogger().error("No active view found");
        }
    }

    void MainViewManager::BackButtonWasPressed(GorillaUI::Components::View* view)
    {
        if (view == mainView)
        {
            if (parentViewManager)
                parentViewManager->DismissViewManager(this);
        }
        else 
        {
            ReplaceTopView(mainView);
        }
        
    }
    /*
    void MainViewManager::DidDeactivate()
    {
        getLogger().info("MainViewManager DidDeactivate was called");
    }
    */
}