#pragma once

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS(GorillaUI::Components, Field, "UnityEngine", "MonoBehaviour", sizeof(Il2CppObject) + sizeof(void*), 
    DECLARE_METHOD(void, HandleInput, Il2CppString* input);

    REGISTER_FUNCTION(Field,
        REGISTER_METHOD(HandleInput);
    )
)