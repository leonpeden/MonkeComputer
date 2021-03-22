#include "GorillaUI/BaseGameViews/BaseGameViewManager.hpp"

#include "GorillaUI/BaseGameViews/BaseGameView.hpp"
#include "GorillaUI/BaseGameViews/ColorChangeView.hpp"
#include "GorillaUI/BaseGameViews/CustomRoomView.hpp"
#include "GorillaUI/BaseGameViews/NameChangeView.hpp"
#include "GorillaUI/BaseGameViews/TurnChangeView.hpp"

#include "GorillaUI.hpp"

DEFINE_CLASS(GorillaUI::BaseGameViewManager);

namespace GorillaUI
{
    void BaseGameViewManager::DidActivate(bool firstActivation)
    {
        if (firstActivation)
        {
            baseGameView = CreateView<BaseGameView*>();
            baseGameView->computer = computer;
            activeView = baseGameView;
        }
    }

    void BaseGameViewManager::NotifyOfKeyPress(int key)
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

    void BaseGameViewManager::BackButtonWasPressed(GorillaUI::Components::View* view)
    {
        if (view != baseGameView)
        {
            ReplaceTopView(baseGameView);
        }
        else 
        {
            if (parentViewManager)
                parentViewManager->DismissViewManager(this);
        }
    }
}