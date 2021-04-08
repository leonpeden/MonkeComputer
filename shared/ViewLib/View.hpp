#pragma once

#include "custom-types/shared/macros.hpp"
#include <string>
#include "UnityEngine/MonoBehaviour.hpp"

namespace GorillaUI
{
    class CustomComputer;
    namespace Components
    {
        class ViewManager; 
        class View;
    }
}

DECLARE_CLASS_CODEGEN(GorillaUI::Components, View, UnityEngine::MonoBehaviour, 
    DECLARE_METHOD(void, Activate);
    DECLARE_METHOD(void, Deactivate);
    DECLARE_INSTANCE_FIELD(bool, activatedBefore);
        
    public:
        std::string text = "";
        GorillaUI::CustomComputer* computer = nullptr;

    REGISTER_FUNCTION(View,
        REGISTER_METHOD(Activate);
        REGISTER_METHOD(Deactivate);
        REGISTER_FIELD(activatedBefore);
    )
)