#include "Elements/Text.hpp"
#include "beatsaber-hook/shared/utils/utils.h"
#include "typedefs.h"

extern Logger& getLogger();

namespace GorillaUI
{
    Text::Text()
    {
        getLogger().info("Default Constructor");
        if (!textPrefab) FindTextPrefab();
        static Il2CppString* name = il2cpp_utils::createcsstr("GUIText", il2cpp_utils::StringType::Manual);
        
        gameObject = CRASH_UNLESS(il2cpp_utils::RunMethod("UnityEngine", "Object", "Instantiate", textPrefab));
        CRASH_UNLESS(il2cpp_utils::RunMethod(gameObject, "set_name", name));

        textComponent = CRASH_UNLESS(il2cpp_utils::RunGenericMethod(gameObject, "GetComponent", std::vector<Il2CppClass*>{il2cpp_utils::GetClassFromName("UnityEngine.UI", "Text")}));
    }

    Text::Text(Il2CppObject* parent, std::string content) : Text()
    {
        Il2CppObject* transform = *il2cpp_utils::RunMethod(gameObject, "get_transform");
        il2cpp_utils::RunMethod(transform, "SetParent", parent);

        static Quaternion rot = CRASH_UNLESS(il2cpp_utils::RunMethod<Quaternion>("UnityEngine", "Quaternion", "get_identity"));
        static Vector3 zero = {0.0f, 0.0f, 0.0f};
        static Vector3 one = {1.0f, 1.0f, 1.0f};

        il2cpp_utils::RunMethod(transform, "set_localPosition", zero);
        il2cpp_utils::RunMethod(transform, "set_localRotation", rot);
        il2cpp_utils::RunMethod(transform, "set_localScale", one);

        set_text(content);
    }

    Text* Text::CreateText(Il2CppObject* parent, std::string content)
    {
        getLogger().info("Creating Text '%s'", content.c_str());

        return new Text(parent, content);
    }

    void Text::set_text(std::string content)
    {
        text = content;
        getLogger().info("Setting '%s' on ptr: %p", content.c_str(), this->textComponent);
        il2cpp_utils::RunMethod(this->textComponent, "set_text", il2cpp_utils::createcsstr(content));
    }

    const std::string& Text::get_text() const
    {
        return text;
    }

    void Text::FindTextPrefab()
    {
        getLogger().info("Prefab  was not defined, defining...");
        Il2CppObject* textGO = CRASH_UNLESS(il2cpp_utils::RunMethod("UnityEngine", "GameObject", "Find", il2cpp_utils::createcsstr("Text")));
        textPrefab = CRASH_UNLESS(il2cpp_utils::RunMethod("UnityEngine", "Object", "Instantiate", textGO));
        getLogger().info("found prefab ptr: %p", *textPrefab);
    }
}