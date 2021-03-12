#pragma once

#include "custom-types/shared/macros.hpp"
#include "ViewLib/View.hpp"
#include "InputHandlers/UISelectionHandler.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, TurnChangeView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, UpdateTurn, int num);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawTurn);
    DECLARE_METHOD(void, OnKeyPressed, int key);

    public:
        GorillaUI::UISelectionHandler* selectionHandler = nullptr;
        GorillaUI::UISelectionHandler* turnValueHandler = nullptr;

    REGISTER_FUNCTION(TurnChangeView,
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(UpdateTurn);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawTurn);
        REGISTER_METHOD(OnKeyPressed);
    )
)