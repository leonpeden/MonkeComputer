#pragma once

#include "custom-types/shared/macros.hpp"
#include "Components/Field.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI::Components, InputField, GorillaUI::Components::Field, 
    DECLARE_METHOD(void, Backspace);
    DECLARE_METHOD(void, Option1);
    DECLARE_METHOD(void, Option2);
    DECLARE_METHOD(void, Option3);
    DECLARE_METHOD(void, Enter);
    //DECLARE_METHOD(void, HandleInput, Il2CppString* input);
    DECLARE_OVERRIDE_METHOD(void, HandleInput, il2cpp_utils::FindMethodUnsafe("GorillaUI::Components", "Field", "HandleInput", 1), Il2CppString* input);

    REGISTER_FUNCTION(InputField,
        REGISTER_METHOD(Backspace);
        REGISTER_METHOD(Option1);
        REGISTER_METHOD(Option2);
        REGISTER_METHOD(Option3);
        REGISTER_METHOD(Enter);
        REGISTER_METHOD(HandleInput);
    )
)