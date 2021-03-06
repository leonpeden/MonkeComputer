#pragma once

#include "Components/View.hpp"
#include "Components/GorillaKeyboardButton.hpp"
#include "custom-types/shared/macros.hpp"

namespace GorillaUI::Components 
{
    class GorillaKeyboardButton; 
    class ViewManager; 
    class View;
}

DECLARE_CLASS(GorillaUI::Components, ViewManager, "UnityEngine", "MonoBehaviour", sizeof(Il2CppObject) + sizeof(void*), 
    DECLARE_METHOD(void, Activate);
    DECLARE_METHOD(void, Deactivate);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, DidDeactivate);
    DECLARE_METHOD(void, PresentViewManager, GorillaUI::Components::ViewManager* manager);
    DECLARE_METHOD(void, DismissViewManager, GorillaUI::Components::ViewManager* manager);
    DECLARE_METHOD(void, ReplaceTopView, GorillaUI::Components::View* view);
    DECLARE_METHOD(void, BackButtonWasPressed, GorillaUI::Components::View* view);
    DECLARE_METHOD(void, PressButton, GorillaKeyboardButton* button);
    
    DECLARE_METHOD(Il2CppObject*, transform);
    DECLARE_METHOD(Il2CppObject*, gameObject);

    DECLARE_INSTANCE_FIELD(GorillaUI::Components::View*, activeView);
    DECLARE_INSTANCE_FIELD(bool, activatedBefore);

    public:
        GorillaUI::Components::ViewManager* parentViewManager = nullptr;
        GorillaUI::Components::ViewManager* childViewManager = nullptr;

    REGISTER_FUNCTION(ViewManager,
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(Activate);
        REGISTER_METHOD(Deactivate);
        REGISTER_METHOD(DidDeactivate);
        REGISTER_METHOD(PresentViewManager);
        REGISTER_METHOD(DismissViewManager);
        REGISTER_METHOD(ReplaceTopView);
        REGISTER_METHOD(BackButtonWasPressed);
        REGISTER_METHOD(PressButton);

        REGISTER_METHOD(transform);
        REGISTER_METHOD(gameObject);

        REGISTER_FIELD(activeView);

        REGISTER_FIELD(activatedBefore);
    )
)