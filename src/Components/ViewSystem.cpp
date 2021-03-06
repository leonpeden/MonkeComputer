#include "Components/ViewSystem.hpp"

DEFINE_CLASS(GorillaUI::Components::ViewSystem);

GorillaUI::Components::ViewManager* GorillaUI::Components::ViewSystem::activeViewManager = nullptr;

namespace GorillaUI::Components
{
    Il2CppObject* ViewSystem::transform()
    {
        return *il2cpp_utils::RunMethod(this, "get_transform");
    }

    Il2CppObject* ViewSystem::gameObject()
    {
        return *il2cpp_utils::RunMethod(this, "get_gameObject");
    }
}