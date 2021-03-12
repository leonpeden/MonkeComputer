#pragma once

#pragma once

#include "custom-types/shared/macros.hpp"
#include "ViewLib/View.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, DetailView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawDetails);
    
    REGISTER_FUNCTION(DetailView,
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawDetails);
    )
)