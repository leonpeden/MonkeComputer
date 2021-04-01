#pragma once

#include "custom-types/shared/macros.hpp"
#include "ViewLib/View.hpp"
#include "InputHandlers/UITextInputHandler.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, NameChangeView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawName);
    DECLARE_METHOD(void, OnKeyPressed, int key);
    DECLARE_INSTANCE_FIELD(bool, lastNameFailed);
    public:
        void EnterName(std::string code);
        GorillaUI::UITextInputHandler* textInputHandler = nullptr;

    REGISTER_FUNCTION(NameChangeView,
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawName);
        REGISTER_METHOD(OnKeyPressed);
        REGISTER_FIELD(lastNameFailed);
    )
)