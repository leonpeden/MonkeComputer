#pragma once

#include "custom-types/shared/macros.hpp"
#include "ViewLib/View.hpp"
#include "InputHandlers/UISelectionHandler.hpp"
#include "InputHandlers/UINumberInputHandler.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, ColorChangeView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, UpdateColor, int num);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawColors);
    DECLARE_METHOD(void, OnKeyPressed, int key);

    public:
        GorillaUI::UISelectionHandler* selectionHandler = nullptr;
        GorillaUI::UINumberInputHandler* numberInputHandlers[3];

    REGISTER_FUNCTION(ColorChangeView,
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(UpdateColor);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawColors);
        REGISTER_METHOD(OnKeyPressed);
    )
)