#pragma once

#include "custom-types/shared/macros.hpp"
#include "ViewLib/View.hpp"
#include "InputHandlers/UIToggleInputHandler.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, VoiceChatView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, UpdateVC, bool value);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawVC);
    DECLARE_METHOD(void, OnKeyPressed, int key);

    public:
        GorillaUI::UIToggleInputHandler* toggleInputHandler = nullptr;

    REGISTER_FUNCTION(
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(UpdateVC);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawVC);
        REGISTER_METHOD(OnKeyPressed);
    )
)