#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/Collider.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "GlobalNamespace/GorillaTriggerBox.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI::Components, WatchActivatorTrigger, GlobalNamespace::GorillaTriggerBox,
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, OnTriggerEnter, UnityEngine::Collider* collider);
    DECLARE_METHOD(void, Update);
    DECLARE_METHOD(bool, IsUpright);

    REGISTER_FUNCTION(
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(OnTriggerEnter);
        REGISTER_METHOD(Update);
        REGISTER_METHOD(IsUpright);
    )
)