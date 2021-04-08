#include "GorillaUI.hpp"
#include "typedefs.h"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Object.hpp"

extern Logger& getLogger();
extern void loadlib();
bool loaded = false;

using namespace UnityEngine;
namespace GorillaUI
{
    static Vector3 zero = {0.0f, 0.0f, 0.0f};
    static Vector3 one = {1.0f, 1.0f, 1.0f};

    Components::ViewManager* CreateViewManager(Il2CppClass* klass)
    {
        getLogger().info("Creating View Manager %s::%s!", klass->namespaze, klass->name);
        GameObject* go = GameObject::New_ctor();
        Object::DontDestroyOnLoad(go);
        Components::ViewManager* result = reinterpret_cast<Components::ViewManager*>(go->AddComponent(il2cpp_utils::GetSystemType(klass)));
        result->activatedBefore = false;
        return result;
    }

    Components::View* CreateView(Il2CppClass* klass)
    {
        getLogger().info("Creating View %s::%s!", klass->namespaze, klass->name);
        
        GameObject* go = GameObject::New_ctor();
        Object::DontDestroyOnLoad(go);

        Components::View* result = reinterpret_cast<Components::View*>(go->AddComponent(il2cpp_utils::GetSystemType(klass)));
        result->activatedBefore = false;
        return result;
    }

    void Init()
    {
        if (loaded) return;
        loaded = true;
        loadlib();
    }
}