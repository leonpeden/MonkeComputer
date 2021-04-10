#pragma once

#include "custom-types/shared/macros.hpp"
#include "ViewLib/View.hpp"
#include "InputHandlers/UISelectionHandler.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, GroupChangeView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, Update);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawGroups);
    DECLARE_METHOD(void, OnKeyPressed, int key);
    DECLARE_METHOD(void, ChangeGroup, int num);
    DECLARE_INSTANCE_FIELD(int, counter);
    public:
        GorillaUI::UISelectionHandler* selectionHandler = nullptr;

    REGISTER_FUNCTION(
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(Update);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawGroups);
        REGISTER_METHOD(OnKeyPressed);
        REGISTER_METHOD(ChangeGroup);
        REGISTER_FIELD(counter);
    )
)