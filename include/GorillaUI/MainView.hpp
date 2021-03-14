#pragma once

#include "custom-types/shared/macros.hpp"
#include "ViewLib/View.hpp"
#include "InputHandlers/UISelectionHandler.hpp"
#include "InputHandlers/UITextInputHandler.hpp"
#include "GorillaUI/ModSettingsView/ModSettingsViewManager.hpp"
#include "GorillaUI/BaseGameViews/BaseGameViewManager.hpp"
#include "GorillaUI/DetailView.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI, MainView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, ShowView, int index);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawSubMenus);
    DECLARE_METHOD(void, OnKeyPressed, int key);
    DECLARE_INSTANCE_FIELD(bool, screenSaver);

    public:
        GorillaUI::UISelectionHandler* selectionHandler = nullptr;
        GorillaUI::ModSettingsViewManager* modSettingsViewManager = nullptr;
        GorillaUI::BaseGameViewManager* baseGameViewManager = nullptr;
        GorillaUI::DetailView* detailView = nullptr;

    REGISTER_FUNCTION(MainView,
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(ShowView);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawSubMenus);
        REGISTER_METHOD(OnKeyPressed);
        REGISTER_FIELD(screenSaver);
    )
)