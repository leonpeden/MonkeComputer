#pragma once

#include "custom-types/shared/macros.hpp"
#include "ViewLib/View.hpp"
#include "InputHandlers/UITextInputHandler.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, CustomRoomView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawCode);
    DECLARE_METHOD(void, OnKeyPressed, int key);

    public:
        void EnterCode(std::string code);
        GorillaUI::UITextInputHandler* textInputHandler = nullptr;

    REGISTER_FUNCTION(CustomRoomView,
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawCode);
        REGISTER_METHOD(OnKeyPressed);
    )
)