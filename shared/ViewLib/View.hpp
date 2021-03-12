#pragma once

#include "custom-types/shared/macros.hpp"
#include <string>

DECLARE_CLASS(GorillaUI::Components, View, "UnityEngine", "MonoBehaviour", sizeof(Il2CppObject) + sizeof(void*), 
    DECLARE_METHOD(void, Activate);
    DECLARE_METHOD(void, Deactivate);
    DECLARE_INSTANCE_FIELD_DEFAULT(bool, activatedBefore, false);
        
    public:
        std::string text = "";
        
    REGISTER_FUNCTION(View,
        REGISTER_METHOD(Activate);
        REGISTER_METHOD(Deactivate);
        REGISTER_FIELD(activatedBefore);
    )
)