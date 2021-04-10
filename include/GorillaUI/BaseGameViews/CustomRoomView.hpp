#pragma once

#include "custom-types/shared/macros.hpp"
#include "ViewLib/View.hpp"
#include "InputHandlers/UITextInputHandler.hpp"
#include "InputHandlers/UIOptionInputHandler.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, CustomRoomView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawCode);
    DECLARE_METHOD(void, OnKeyPressed, int key);
    DECLARE_METHOD(void, Update);
    DECLARE_INSTANCE_FIELD(float, lastUpdatedTime);
    public:
        void EnterCode(std::string code);
        GorillaUI::UITextInputHandler* textInputHandler = nullptr;
        GorillaUI::UIOptionInputHandler* optionInputHandler = nullptr;

    REGISTER_FUNCTION(
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawCode);
        REGISTER_METHOD(OnKeyPressed);
        REGISTER_METHOD(Update);
        REGISTER_FIELD(lastUpdatedTime);
    )
)