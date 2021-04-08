#include "GorillaUI/ModSettingsView/ModSettingsViewManager.hpp"
#include "GorillaUI/ModSettingsView/ModSettingsView.hpp"
#include "GorillaUI.hpp"

DEFINE_TYPE(GorillaUI::ModSettingsViewManager);

namespace GorillaUI
{
    void ModSettingsViewManager::DidActivate(bool firstActivation)
    {
        if (firstActivation)
        {
            listView = CreateView<ModSettingsView*>();
            listView->computer = computer;
            activeView = listView;
        }
    }

    void ModSettingsViewManager::NotifyOfKeyPress(int key)
    {
        if (key == (int)EKeyboardKey::Back)
        {
            il2cpp_utils::RunMethod(this, "BackButtonWasPressed", activeView);
        }
        else
        {
            if (activeView)
            {
                il2cpp_utils::RunMethod(activeView, "OnKeyPressed", key);
            }
        }
    }

    void ModSettingsViewManager::BackButtonWasPressed(GorillaUI::Components::View* view)
    {
        if (view == listView)
        {
            if (parentViewManager)
                parentViewManager->DismissViewManager(this);
        }
        else 
        {
            ReplaceTopView(listView);
        }
    }
}