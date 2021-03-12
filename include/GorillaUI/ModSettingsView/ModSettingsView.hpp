#pragma once

#include "custom-types/shared/macros.hpp"
#include "ViewLib/View.hpp"
#include "InputHandlers/UISelectionHandler.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, ModSettingsView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, ShowModView, int index);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawMods);
    DECLARE_METHOD(void, OnKeyPressed, int key);
    
    public:
        GorillaUI::UISelectionHandler* selectionHandler = nullptr;
    
    REGISTER_FUNCTION(ModSettingsView,
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(ShowModView);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawMods);
        REGISTER_METHOD(OnKeyPressed);
    )
)