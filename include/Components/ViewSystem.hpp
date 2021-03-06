#pragma once

#include "custom-types/shared/macros.hpp"

#include "Components/ViewManager.hpp"
#include "Components/View.hpp"
#include "typedefs.h"

DECLARE_CLASS(GorillaUI::Components, ViewSystem, "UnityEngine", "MonoBehaviour", sizeof(Il2CppObject) + sizeof(void*), 
    DECLARE_STATIC_FIELD(GorillaUI::Components::ViewManager*, activeViewManager);
    DECLARE_METHOD(Il2CppObject*, transform);
    DECLARE_METHOD(Il2CppObject*, gameObject);
    REGISTER_FUNCTION(ViewSystem,
        REGISTER_FIELD(activeViewManager);
        REGISTER_METHOD(transform);
        REGISTER_METHOD(gameObject);
    )
)