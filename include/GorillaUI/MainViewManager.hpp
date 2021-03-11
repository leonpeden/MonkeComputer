#pragma once

#include "EKeyboardKey.hpp"
#include "custom-types/shared/macros.hpp"
#include "ViewLib/ViewManager.hpp"
#include "ViewLib/View.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, MainViewManager, GorillaUI::Components::ViewManager, 
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, NotifyOfKeyPress, int key);
    DECLARE_METHOD(void, BackButtonWasPressed, GorillaUI::Components::View* view);
    DECLARE_INSTANCE_FIELD(Components::View*, mainView);

    REGISTER_FUNCTION(MainViewManager,
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(NotifyOfKeyPress);
        REGISTER_METHOD(BackButtonWasPressed);
        REGISTER_FIELD(mainView);
    )
)