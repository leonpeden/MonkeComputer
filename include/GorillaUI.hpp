#pragma once
#include "Elements/Text.hpp"
#include "Elements/Canvas.hpp"

#include "Components/GorillaKeyboardButton.hpp"
#include "Components/ViewSystem.hpp"
#include "Components/ViewManager.hpp"
#include "Components/View.hpp"
#include "Components/InputField.hpp"

namespace GorillaUI
{
    Text* CreateText(Il2CppObject* parent, std::string content);
    Canvas* CreateCanvas();
    Canvas* CreateCanvas(Vector3 position, Vector3 rotation);
    Canvas* CreateCanvas(Vector3 position, Vector3 rotation, Vector3 scale);

    Components::ViewManager* CreateViewManager(Il2CppClass* klass);
    Components::View* CreateView(Il2CppClass* klass);

    Components::ViewSystem* CreateViewSystem(Il2CppClass* initialViewManager, Vector3 position, Vector3 euler, Vector3 scale);
    Components::ViewSystem* CreateViewSystem(Il2CppClass* initialViewManager, Vector3 position, Vector3 euler);
    Components::ViewSystem* CreateViewSystem(Il2CppClass* initialViewManager);

    template<class T = Il2CppObject*>
    Components::ViewSystem* CreateViewSystem()
    {
        return CreateViewSystem(classof(T));
    }

    template<class T = Il2CppObject*>
    Components::ViewSystem* CreateViewSystem(Vector3 position, Vector3 euler)
    {
        return CreateViewSystem(classof(T), position, euler);
    }

    template<class T = Il2CppObject*>
    Components::ViewSystem* CreateViewSystem(Vector3 position, Vector3 euler, Vector3 scale)
    {
        Components::ViewSystem* viewSystem = CreateViewSystem(classof(T), position, euler, scale);
        T manager = CreateViewManager<T>();
        manager->Activate();
        return viewSystem;
    }

    template<class T = Il2CppObject*>
    T CreateView()
    {
        return reinterpret_cast<T>(CreateView(classof(T)));
    }

    template<class T = Il2CppObject*>
    T CreateViewManager()
    {
        Il2CppClass* klass = classof(T);
        Il2CppObject* go = CRASH_UNLESS(il2cpp_utils::New(il2cpp_utils::GetClassFromName("UnityEngine", "GameObject")));
        il2cpp_utils::RunMethod(go, "DontDestroyOnLoad", go);
        T result = *il2cpp_utils::RunGenericMethod<T>(go, "AddComponent", std::vector<Il2CppClass*>{klass});
        result->activatedBefore = false;
        return result;
    }
}   