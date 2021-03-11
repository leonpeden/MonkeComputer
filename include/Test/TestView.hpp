#pragma once

#include "custom-types/shared/macros.hpp"
#include "ViewLib/View.hpp"
#include "InputHandlers/UISelectionHandler.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, TestView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, OnKeyPressed, int key);

    public:
        GorillaUI::UISelectionHandler* selectionHandler = nullptr;

    REGISTER_FUNCTION(TestView,
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(OnKeyPressed);
    )
)