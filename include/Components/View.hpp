#pragma once
#include "custom-types/shared/macros.hpp"

DECLARE_CLASS(GorillaUI::Components, View, "UnityEngine", "MonoBehaviour", sizeof(Il2CppObject) + sizeof(void*), 
    DECLARE_METHOD(void, Activate);
    DECLARE_METHOD(void, Deactivate);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, DidDeactivate);
    DECLARE_METHOD(void, HandleInput, Il2CppString* input);
    DECLARE_INSTANCE_FIELD_DEFAULT(bool, activatedBefore, false);
    
    DECLARE_METHOD(Il2CppObject*, transform);
    DECLARE_METHOD(Il2CppObject*, gameObject);

    REGISTER_FUNCTION(View,
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(Activate);
        REGISTER_METHOD(Deactivate);
        REGISTER_METHOD(DidDeactivate);
        REGISTER_METHOD(HandleInput);
        
        REGISTER_METHOD(transform);
        REGISTER_METHOD(gameObject);

        REGISTER_FIELD(activatedBefore);
    )
)