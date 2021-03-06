#pragma once

#include "custom-types/shared/macros.hpp"
#include "Components/View.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, MainView, GorillaUI::Components::View, 
    //DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("GorillaUI::Components", "View", "DidActivate", 1), bool firstActivation);

    REGISTER_FUNCTION(MainView,
        REGISTER_METHOD(DidActivate);
    )
)