#include "GorillaUI.hpp"

extern Logger& getLogger();

namespace GorillaUI
{
    static Vector3 zero = {0.0f, 0.0f, 0.0f};
    static Vector3 one = {1.0f, 1.0f, 1.0f};

    Text* CreateText(Il2CppObject* parent, std::string content)
    {
        return Text::CreateText(parent, content);
    }

    Canvas* CreateCanvas()
    {
        return Canvas::CreateCanvas(zero, zero);
    }

    Canvas* CreateCanvas(Vector3 position, Vector3 rotation)
    {
        return Canvas::CreateCanvas(position, rotation);
    }

    Canvas* CreateCanvas(Vector3 position, Vector3 rotation, Vector3 scale)
    {
        return Canvas::CreateCanvas(scale, position, rotation);
    }

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
        getLogger().info("Creating View %s%s!", klass->namespaze, klass->name);
        Canvas* canvas = CreateCanvas();
        Il2CppObject* go = canvas->get_gameObject();
        il2cpp_utils::RunMethod(go, "DontDestroyOnLoad", go);
        CRASH_UNLESS(il2cpp_utils::New(il2cpp_utils::GetClassFromName("UnityEngine", "GameObject")));
        Il2CppObject* transform = CRASH_UNLESS(il2cpp_utils::RunMethod(go, "get_transform"));
        Components::View* result = *il2cpp_utils::RunGenericMethod<Components::View*>(go, "AddComponent", std::vector<Il2CppClass*>{klass});
        result->activatedBefore = false;
        return result;
    }

    Components::ViewSystem* CreateViewSystem(Il2CppClass* initialViewManager, Vector3 position, Vector3 euler, Vector3 scale)
    {
        getLogger().info("Creating View System!");
        Il2CppObject* go = CRASH_UNLESS(il2cpp_utils::New(il2cpp_utils::GetClassFromName("UnityEngine", "GameObject")));
        il2cpp_utils::RunMethod(go, "DontDestroyOnLoad", go);

        Components::ViewSystem* result = *il2cpp_utils::RunGenericMethod<Components::ViewSystem*>(go, "AddComponent", std::vector<Il2CppClass*>{il2cpp_utils::GetClassFromName("GorillaUI::Components", "ViewSystem")});
        Il2CppObject* transform = CRASH_UNLESS(il2cpp_utils::RunMethod(result, "get_transform"));
        CRASH_UNLESS(il2cpp_utils::RunMethod(transform, "set_localScale", scale));
        CRASH_UNLESS(il2cpp_utils::RunMethod(transform, "set_position", position));
        CRASH_UNLESS(il2cpp_utils::RunMethod(transform, "set_localEulerAngles", euler));
        Il2CppObject* manager = (Il2CppObject*)CreateViewManager(initialViewManager);
        il2cpp_utils::RunMethod(manager, "Activate");
        //manager->Activate();
        return result;
    }

    Components::ViewSystem* CreateViewSystem(Il2CppClass* initialViewManager, Vector3 position, Vector3 euler)
    {
        static Vector3 scale = {0.0025f, 0.0025f, 0.0025f};
        return CreateViewSystem(initialViewManager, position, euler, scale);
    }

    Components::ViewSystem* CreateViewSystem(Il2CppClass* initialViewManager)
    {
        return CreateViewSystem(initialViewManager, zero, zero);
    }
}