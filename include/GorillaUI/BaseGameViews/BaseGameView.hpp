#pragma once

#include "custom-types/shared/macros.hpp"
#include "ViewLib/View.hpp"
#include "InputHandlers/UISelectionHandler.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, BaseGameView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, ShowView, int index);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawViews);
    DECLARE_METHOD(void, OnKeyPressed, int key);
    DECLARE_INSTANCE_FIELD(Components::View*, customRoomView);
    DECLARE_INSTANCE_FIELD(Components::View*, nameChangeView);
    DECLARE_INSTANCE_FIELD(Components::View*, colorChangeView);
    DECLARE_INSTANCE_FIELD(Components::View*, turnChangeView);
    DECLARE_INSTANCE_FIELD(Components::View*, micChangeView);
    DECLARE_INSTANCE_FIELD(Components::View*, groupChangeView);
    DECLARE_INSTANCE_FIELD(Components::View*, queueChangeView);

    public:
        GorillaUI::UISelectionHandler* selectionHandler = nullptr;
        bool old = true;
    
    REGISTER_FUNCTION(
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(ShowView);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawViews);
        REGISTER_METHOD(OnKeyPressed);
        REGISTER_FIELD(customRoomView);
        REGISTER_FIELD(nameChangeView);
        REGISTER_FIELD(colorChangeView);
        REGISTER_FIELD(turnChangeView);
        REGISTER_FIELD(micChangeView);
        REGISTER_FIELD(groupChangeView);
        REGISTER_FIELD(queueChangeView);

    )
)