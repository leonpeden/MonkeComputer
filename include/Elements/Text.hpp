#pragma once
#include <string>
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "beatsaber-hook/shared/utils/typedefs-wrappers.hpp"

namespace GorillaUI
{
    class Text
    {
        public:
            static Text* CreateText(Il2CppObject* parent, std::string content);
            void set_text(std::string content);
            const std::string& get_text() const;
        private:
            Text();
            Text(Il2CppObject* parent, std::string content);
            static void FindTextPrefab();
            std::string text = "";
            Il2CppObject* gameObject;
            Il2CppObject* textComponent;
            static inline Il2CppObject* textPrefab = nullptr;
    };
}