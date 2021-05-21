#pragma once

#include "custom-types/shared/macros.hpp"

#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Transform.hpp"

DECLARE_CLASS_CODEGEN(GorillaUI::Components, BillboardedWatch, UnityEngine::MonoBehaviour,
    DECLARE_METHOD(void, Update);
    DECLARE_METHOD(void, OnEnable);
    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, camTransform);

    REGISTER_FUNCTION(
        REGISTER_METHOD(Update);
        REGISTER_METHOD(OnEnable);
        REGISTER_FIELD(camTransform);
    )   
)