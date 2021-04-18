#pragma once
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "beatsaber-hook/shared/utils/typedefs-wrappers.hpp"
#include "../typedefs.h"

#include "UnityEngine/UI/Text.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Renderer.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Texture2D.hpp"

namespace GorillaUI
{
    class CustomScreenInfo
    {
        public:
            UnityEngine::UI::Text* text = nullptr;
            UnityEngine::Transform* transform = nullptr;
            UnityEngine::Renderer* renderer = nullptr;
            Array<UnityEngine::Material*>* materials = nullptr;

            void set_fontSize(int size);
            int get_fontSize();

            void set_color(UnityEngine::Color color);
            UnityEngine::Color get_color();

            void set_text(std::string newText);
            std::string get_text();

            void set_texture(UnityEngine::Texture2D* tex);
            UnityEngine::Texture2D* get_texture();
    };
}