#pragma once

#include "custom-types/shared/macros.hpp"
#include <string>

namespace GorillaUI
{
    class CustomComputer;
    namespace Components
    {
        class ViewManager; 
        class View;
    }
}

DECLARE_CLASS(GorillaUI::Components, View, "UnityEngine", "MonoBehaviour", sizeof(Il2CppObject) + sizeof(void*) * 2 + sizeof(std::string), 
    DECLARE_METHOD(void, Activate);
    DECLARE_METHOD(void, Deactivate);
    DECLARE_INSTANCE_FIELD_DEFAULT(bool, activatedBefore, false);
        
    public:
        std::string text = "";
        GorillaUI::CustomComputer* computer = nullptr;

    REGISTER_FUNCTION(View,
        REGISTER_METHOD(Activate);
        REGISTER_METHOD(Deactivate);
        REGISTER_FIELD(activatedBefore);
    )
)