#include "GorillaUI.hpp"
#include "typedefs.h"

extern Logger& getLogger();
extern void loadlib();
bool loaded = false;

namespace GorillaUI
{
    static Vector3 zero = {0.0f, 0.0f, 0.0f};
    static Vector3 one = {1.0f, 1.0f, 1.0f};

    Components::ViewManager* CreateViewManager(Il2CppClass* klass)
    {
        getLogger().info("Creating View Manager %s::%s!", klass->namespaze, klass->name);
        Il2CppObject* go = CRASH_UNLESS(il2cpp_utils::New(il2cpp_utils::GetClassFromName("UnityEngine", "GameObject")));
        il2cpp_utils::RunMethod(go, "DontDestroyOnLoad", go);
        Components::ViewManager* result = *il2cpp_utils::RunGenericMethod<Components::ViewManager*>(go, "AddComponent", std::vector<Il2CppClass*>{klass});
        result->activatedBefore = false;
        return result;
    }

    Components::View* CreateView(Il2CppClass* klass)
    {
        getLogger().info("Creating View %s::%s!", klass->namespaze, klass->name);
        
        Il2CppObject* go = *il2cpp_utils::New(il2cpp_utils::GetClassFromName("UnityEngine", "GameObject"));
        
        il2cpp_utils::RunMethod(go, "DontDestroyOnLoad", go);

        Components::View* result = *il2cpp_utils::RunGenericMethod<Components::View*>(go, "AddComponent", std::vector<Il2CppClass*>{klass});
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