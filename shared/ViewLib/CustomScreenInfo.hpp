#pragma once
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "../typedefs.h"

namespace GorillaUI
{
    class CustomScreenInfo
    {
        public:
            Il2CppObject* text;
            Il2CppObject* transform;
            Il2CppObject* renderer;
            Array<Il2CppObject*>* materials;

            void set_fontSize(int size);
            int get_fontSize();

            void set_color(Color color);
            Color get_color();

            void set_text(std::string newText);
            std::string get_text();
    };
}