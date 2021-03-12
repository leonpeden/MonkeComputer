#pragma once

#include "custom-types/shared/macros.hpp"
#include "../ViewLib/CustomComputer.hpp"
#include "../EKeyboardKey.hpp"
#include "../typedefs.h"

namespace GorillaUI::Components
{
    class ViewSystem;
}

namespace GorillaUI {
    class CustomComputer;
}

DECLARE_CLASS(GorillaUI::Components, GorillaKeyboardButton, "", "GorillaTriggerBox", sizeof(Il2CppObject) + sizeof(void*) * 2 + sizeof(int) + sizeof(float) * 3,
    DECLARE_METHOD(void, OnTriggerEnter, Il2CppObject* collider);
    DECLARE_METHOD(void, OnTriggerExit, Il2CppObject* collider);
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, BumpIn);
    DECLARE_METHOD(void, BumpOut);
    DECLARE_INSTANCE_FIELD(bool, isOnCooldown);
    DECLARE_INSTANCE_FIELD(bool, functionKey);
    DECLARE_INSTANCE_FIELD(Il2CppObject*, material);
    DECLARE_INSTANCE_FIELD(float, pressTime);
    
    public:
        EKeyboardKey key;
        void Init(GorillaUI::CustomComputer* computer, EKeyboardKey key);
        void Init(GorillaUI::CustomComputer* computer, EKeyboardKey key, std::string text);
        void Init(GorillaUI::CustomComputer* computer, EKeyboardKey key, std::string text, Color buttonColor);

    private:
        Color originalColor;
        GorillaUI::CustomComputer* computer;

    REGISTER_FUNCTION(GorillaKeyboardButton,
        REGISTER_METHOD(OnTriggerEnter);
        REGISTER_METHOD(OnTriggerExit);
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(BumpIn);
        REGISTER_METHOD(BumpOut);
        REGISTER_FIELD(isOnCooldown);
        REGISTER_FIELD(material);
        REGISTER_FIELD(pressTime);
        REGISTER_FIELD(functionKey);
    )
)