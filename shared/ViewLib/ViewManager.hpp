#pragma once

#include "../ViewLib/View.hpp"
#include "custom-types/shared/macros.hpp"
#include <map> 

#include "UnityEngine/MonoBehaviour.hpp"


namespace GorillaUI
{
    class CustomComputer;
    namespace Components
    {
        class ViewManager; 
        class View;
    }
}

DECLARE_CLASS_CODEGEN(GorillaUI::Components, ViewManager, UnityEngine::MonoBehaviour, 
    DECLARE_METHOD(void, Activate);
    DECLARE_METHOD(void, Deactivate);
    DECLARE_METHOD(void, PresentViewManager, GorillaUI::Components::ViewManager* manager);
    DECLARE_METHOD(void, DismissViewManager, GorillaUI::Components::ViewManager* manager);
    DECLARE_METHOD(void, ReplaceTopView, GorillaUI::Components::View* view);
    
    DECLARE_INSTANCE_FIELD(GorillaUI::Components::View*, activeView);
    DECLARE_INSTANCE_FIELD(bool, activatedBefore);

    public:
        GorillaUI::Components::ViewManager* parentViewManager = nullptr;
        GorillaUI::Components::ViewManager* childViewManager = nullptr;
        GorillaUI::CustomComputer* computer = nullptr;
        
    REGISTER_FUNCTION(ViewManager,
        REGISTER_METHOD(Activate);
        REGISTER_METHOD(Deactivate);
        REGISTER_METHOD(PresentViewManager);
        REGISTER_METHOD(DismissViewManager);
        REGISTER_METHOD(ReplaceTopView);

        REGISTER_FIELD(activeView);

        REGISTER_FIELD(activatedBefore);
    )
)