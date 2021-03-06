#pragma once
#include "custom-types/shared/macros.hpp"

namespace GorillaUI::Components
{
    class ViewSystem;
}

DECLARE_CLASS(GorillaUI::Components, GorillaKeyboardButton, "", "GorillaTriggerBox", sizeof(Il2CppObject) + sizeof(void*), 
    DECLARE_METHOD(void, OnTriggerEnter, Il2CppObject* collider);

    DECLARE_INSTANCE_FIELD(Il2CppString*, characterString);
    DECLARE_INSTANCE_FIELD(float, pressTime);

    REGISTER_FUNCTION(GorillaKeyboardButton,
        REGISTER_METHOD(OnTriggerEnter);
        REGISTER_FIELD(characterString);
        REGISTER_FIELD(pressTime);
    )
)