#include "GorillaUI/MainViewManager.hpp"
#include "GorillaUI.hpp"

DEFINE_CLASS(GorillaUI::MainViewManager);

using namespace GorillaUI::Components;

extern Logger& getLogger();

namespace GorillaUI
{
    void MainViewManager::DidActivate(bool firstActivation)
    {
        if (firstActivation)
        {
            activeView = CreateView(il2cpp_utils::GetClassFromName("GorillaUI", "MainView"));
            //ReplaceTopView(view);

            getLogger().info("Main View Manager says hello!");
        }
    }
}