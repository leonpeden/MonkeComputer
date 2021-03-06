#include "Components/View.hpp"
#include "typedefs.h"

DEFINE_CLASS(GorillaUI::Components::View);

extern Logger& getLogger();

namespace GorillaUI::Components
{
    void View::Activate()
    {
        static Vector3 zero = {0.0f, 0.0f, 0.0f};
        Il2CppObject* viewTransform = transform();
        il2cpp_utils::RunMethod(viewTransform, "set_localPosition", zero);
        il2cpp_utils::RunMethod(viewTransform, "set_localEulerAngles", zero);
        DidActivate(!activatedBefore);
        activatedBefore = true;
    }

    void View::Deactivate()
    {
        DidDeactivate();
        il2cpp_utils::RunMethod(gameObject(), "SetActive", false);
    }

    void View::DidActivate(bool firstActivation)
    {
        getLogger().info("Default View DidActivate was called, firstActivation: %d", firstActivation);
    }

    void View::DidDeactivate()
    {
        getLogger().info("Default View DidDeactivate was called");
    }

    void View::HandleInput(Il2CppString* input)
    {
        std::string val = to_utf8(csstrtostr(input));
        getLogger().info("Character input '%s' was given!", val.c_str());
    }

    Il2CppObject* View::transform()
    {
        return *il2cpp_utils::RunMethod(this, "get_transform");
    }

    Il2CppObject* View::gameObject()
    {
        return *il2cpp_utils::RunMethod(this, "get_gameObject");
    }
}
