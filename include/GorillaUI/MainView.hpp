#pragma once

#include "custom-types/shared/macros.hpp"
#include "ViewLib/View.hpp"
#include "InputHandlers/UISelectionHandler.hpp"
#include "InputHandlers/UITextInputHandler.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, MainView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, ShowModView, int index);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, DidDeactivate);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawMods);
    DECLARE_METHOD(void, OnKeyPressed, int key);
    //DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("GorillaUI::Components", "View", "DidActivate", 1), bool firstActivation);

    public:
        GorillaUI::UISelectionHandler* selectionHandler = nullptr;
        GorillaUI::UITextInputHandler* textInputHandler = nullptr;
    
    REGISTER_FUNCTION(MainView,
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(ShowModView);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(DidDeactivate);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawMods);
        REGISTER_METHOD(OnKeyPressed);
    )
)