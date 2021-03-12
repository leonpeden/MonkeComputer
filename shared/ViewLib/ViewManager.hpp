#pragma once

#include "../ViewLib/View.hpp"
#include "custom-types/shared/macros.hpp"
#include <map> 

namespace GorillaUI::Components 
{
    class ViewManager; 
    class View;
}

DECLARE_CLASS(GorillaUI::Components, ViewManager, "UnityEngine", "MonoBehaviour", sizeof(Il2CppObject) + sizeof(void*) * 3, 
    DECLARE_METHOD(void, Activate);
    DECLARE_METHOD(void, Deactivate);
    DECLARE_METHOD(void, PresentViewManager, GorillaUI::Components::ViewManager* manager);
    DECLARE_METHOD(void, DismissViewManager, GorillaUI::Components::ViewManager* manager);
    DECLARE_METHOD(void, ReplaceTopView, GorillaUI::Components::View* view);
    
    DECLARE_METHOD(Il2CppObject*, transform);
    DECLARE_METHOD(Il2CppObject*, gameObject);

    DECLARE_INSTANCE_FIELD(GorillaUI::Components::View*, activeView);
    DECLARE_INSTANCE_FIELD(bool, activatedBefore);

    public:
        GorillaUI::Components::ViewManager* parentViewManager = nullptr;
        GorillaUI::Components::ViewManager* childViewManager = nullptr;

    REGISTER_FUNCTION(ViewManager,
        REGISTER_METHOD(Activate);
        REGISTER_METHOD(Deactivate);
        REGISTER_METHOD(PresentViewManager);
        REGISTER_METHOD(DismissViewManager);
        REGISTER_METHOD(ReplaceTopView);

        REGISTER_METHOD(transform);
        REGISTER_METHOD(gameObject);

        REGISTER_FIELD(activeView);

        REGISTER_FIELD(activatedBefore);
    )
)