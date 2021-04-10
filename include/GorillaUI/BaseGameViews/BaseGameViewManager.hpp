#pragma once

#include "EKeyboardKey.hpp"
#include "custom-types/shared/macros.hpp"
#include "ViewLib/ViewManager.hpp"
#include "ViewLib/View.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, BaseGameViewManager, GorillaUI::Components::ViewManager, 
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, NotifyOfKeyPress, int key);
    DECLARE_METHOD(void, BackButtonWasPressed, GorillaUI::Components::View* view);
    
    DECLARE_INSTANCE_FIELD(Components::View*, baseGameView);

    REGISTER_FUNCTION(
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(NotifyOfKeyPress);
        REGISTER_METHOD(BackButtonWasPressed);
        REGISTER_FIELD(baseGameView);
    )
)