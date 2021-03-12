#pragma once

#include <map>

#include "custom-types/shared/macros.hpp"
#include "../EKeyboardKey.hpp"

#include "../ViewLib/CustomScreenInfo.hpp"
#include "../ViewLib/GorillaKeyboardButton.hpp"
#include "../ViewLib/ViewManager.hpp"
#include "../ViewLib/View.hpp"

#include "../typedefs.h"

namespace GorillaUI::Components {
    class GorillaKeyboardButton;
}

using keymap = std::map<GorillaUI::EKeyboardKey, GorillaUI::Components::GorillaKeyboardButton*>;

DECLARE_CLASS(GorillaUI, CustomComputer, "UnityEngine", "MonoBehaviour", sizeof(Il2CppObject) + sizeof(void*),
    DECLARE_METHOD(void, PressButton, GorillaUI::Components::GorillaKeyboardButton* button);
    DECLARE_METHOD(void, ReplaceKeys);
    DECLARE_METHOD(static void, Redraw);
    DECLARE_METHOD(void, SetBG, float r, float g, float b);
    DECLARE_INSTANCE_FIELD(bool, initialized);
    DECLARE_INSTANCE_FIELD(Il2CppObject*, gorillaComputer);

    private:
        GorillaUI::Components::GorillaKeyboardButton* CreateKeyNoInit(Il2CppObject* prefab, std::string goName, Vector3 offset, EKeyboardKey key);
        GorillaUI::Components::GorillaKeyboardButton* CreateKey(Il2CppObject* prefab, std::string goName, Vector3 offset, EKeyboardKey key);
        GorillaUI::Components::GorillaKeyboardButton* CreateKey(Il2CppObject* prefab, std::string goName, Vector3 offset, EKeyboardKey key, std::string label);
        GorillaUI::Components::GorillaKeyboardButton* CreateKey(Il2CppObject* prefab, std::string goName, Vector3 offset, EKeyboardKey key, std::string label, Color color);
        CustomScreenInfo CreateMonitor();

        keymap keys;
        CustomScreenInfo screenInfo;
    public:
        void set_screenColor(Color color);
        GorillaUI::Components::ViewManager* activeViewManager = nullptr;
        void Init(GorillaUI::Components::View* initialView);
        static inline GorillaUI::CustomComputer* instance = nullptr;

    REGISTER_FUNCTION(CustomComputer,
        REGISTER_METHOD(PressButton);
        REGISTER_METHOD(ReplaceKeys);
        REGISTER_METHOD(SetBG);
        REGISTER_METHOD(Redraw);
        REGISTER_FIELD(gorillaComputer);
        REGISTER_FIELD(initialized);
    )
)