#include "ViewLib/ViewManager.hpp"
#include "KeyExtension.hpp"
#include "typedefs.h"
#include "ViewLib/CustomComputer.hpp"

DEFINE_CLASS(GorillaUI::Components::ViewManager);

extern Logger& getLogger();

namespace GorillaUI::Components
{
    void ViewManager::Activate()
    {
        il2cpp_utils::RunMethod(this, "DidActivate", !activatedBefore);
        if (activeView)
            activeView->Activate();
        activatedBefore = true;
    }

    void ViewManager::Deactivate()
    {
        il2cpp_utils::RunMethod(this, "DidDeactivate");
    }
   
    void ViewManager::PresentViewManager(GorillaUI::Components::ViewManager* manager)
    {
        static Vector3 zero = {0.0f, 0.0f, 0.0f};
        childViewManager = manager;
        manager->parentViewManager = this;
        il2cpp_utils::RunMethod(manager->transform(), "SetParent", transform());
        il2cpp_utils::RunMethod(manager->transform(), "set_localPosition", zero);
        il2cpp_utils::RunMethod(manager->transform(), "set_localEulerAngles", zero);

        activeView->Deactivate();
        manager->Activate();
        CustomComputer::instance->activeViewManager = manager;
    }

    void ViewManager::DismissViewManager(GorillaUI::Components::ViewManager* manager)
    {
        childViewManager = nullptr;
        manager->activeView->Deactivate();
        manager->Deactivate();
        activeView->Activate();
        CustomComputer::instance->activeViewManager = this;
        CustomComputer::Redraw();
    }

    void ViewManager::ReplaceTopView(GorillaUI::Components::View* view)
    {
        if (activeView) activeView->Deactivate();
        activeView = view;
        activeView->Activate();
        CustomComputer::instance->Redraw();
    }

    Il2CppObject* ViewManager::transform()
    {
        return *il2cpp_utils::RunMethod(this, "get_transform");
    }

    Il2CppObject* ViewManager::gameObject()
    {
        return *il2cpp_utils::RunMethod(this, "get_gameObject");
    }
}