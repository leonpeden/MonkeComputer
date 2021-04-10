#pragma once

#include "custom-types/shared/macros.hpp"
#include "ViewLib/View.hpp"
#include "InputHandlers/UISelectionHandler.hpp"
#include "GorillaUI/ModSettingsView/ModSettingsViewManager.hpp"
#include "GorillaUI/BaseGameViews/BaseGameViewManager.hpp"
#include "GorillaUI/DetailView.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, CustomQueueView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, JoinQueue, int index);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawQueues);
    DECLARE_METHOD(void, OnKeyPressed, int key);
    DECLARE_INSTANCE_FIELD(void*, selectionHandler);

    REGISTER_FUNCTION(
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(JoinQueue);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawQueues);
        REGISTER_METHOD(OnKeyPressed);
        REGISTER_FIELD(selectionHandler);
    )
)