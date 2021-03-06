#pragma once
#include <string>
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "beatsaber-hook/shared/utils/typedefs-wrappers.hpp"
#include "typedefs.h"

namespace GorillaUI
{
    class Canvas
    {
        public:
            static Canvas* CreateCanvas(Vector3 position, Vector3 rotation);
            static Canvas* CreateCanvas(Vector3 scale, Vector3 position, Vector3 rotation);
            Il2CppObject* get_transform();
            Il2CppObject* get_gameObject();
            void set_scale(Vector3 scale);
            void set_position(Vector3 position);
            void set_localEulerAngles(Vector3 angles);
            void set_rotation(Quaternion rotation);
            Vector3 get_scale();
            Vector3 get_position();
            Vector3 get_localEulerAngles();
            Quaternion get_rotation();
        private:
            Canvas();
            Canvas(Vector3 position, Vector3 rotation);
            Canvas(Vector3 scale, Vector3 position, Vector3 rotation);
            static void FindCanvasPrefab();
            Il2CppObject* gameObject;
            static inline Il2CppObject* canvasPrefab = nullptr;
    };
}