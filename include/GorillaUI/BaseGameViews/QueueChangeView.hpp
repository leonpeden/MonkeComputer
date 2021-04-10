#pragma once

#include "custom-types/shared/macros.hpp"
#include "ViewLib/View.hpp"
#include "InputHandlers/UISelectionHandler.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, QueueChangeView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawQueues);
    DECLARE_METHOD(void, OnKeyPressed, int key);
    DECLARE_METHOD(void, ChangeQueue, int num);
    public:
        GorillaUI::UISelectionHandler* selectionHandler = nullptr;

    REGISTER_FUNCTION(
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawQueues);
        REGISTER_METHOD(OnKeyPressed);
        REGISTER_METHOD(ChangeQueue);
    )
)