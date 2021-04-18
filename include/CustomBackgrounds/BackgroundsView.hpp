#pragma once

#include "ViewLib/View.hpp"
#include "InputHandlers/UISelectionHandler.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, BackgroundsView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, LoadTexture, int index);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawBackgrounds);
    DECLARE_METHOD(void, OnKeyPressed, int key);
    DECLARE_INSTANCE_FIELD(int, bgCount);
    DECLARE_INSTANCE_FIELD(int, pageCount);
    public:
        GorillaUI::UISelectionHandler* selectionHandler;
        GorillaUI::UISelectionHandler* pageSelectionHandler;

    REGISTER_FUNCTION(
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(LoadTexture);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawBackgrounds);
        REGISTER_METHOD(OnKeyPressed);
        REGISTER_FIELD(bgCount);
        REGISTER_FIELD(pageCount);
    )
)