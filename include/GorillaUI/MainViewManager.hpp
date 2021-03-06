#pragma once

#include "custom-types/shared/macros.hpp"
#include "Components/ViewManager.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, MainViewManager, GorillaUI::Components::ViewManager, 
    //DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("GorillaUI::Components", "ViewManager", "DidActivate", 1), bool firstActivation);

    REGISTER_FUNCTION(MainViewManager,
        REGISTER_METHOD(DidActivate);
    )
)