#include "Components/ViewManager.hpp"
#include "Components/ViewSystem.hpp"

DEFINE_CLASS(GorillaUI::Components::ViewManager);

extern Logger& getLogger();

namespace GorillaUI::Components
{
    void ViewManager::Activate()
    {
        this->DidActivate(!activatedBefore);
        if (activeView) activeView->Activate();
        activatedBefore = true;
    }

    void ViewManager::Deactivate()
    {
        DidDeactivate();
    }

    void ViewManager::DidActivate(bool firstActivation)
    {
        getLogger().info("Default ViewManager DidActivate was called, firstActivation: %d", firstActivation);
    }

    void ViewManager::DidDeactivate()
    {
        getLogger().info("Default ViewManager DidDeactivate was called");
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
        ViewSystem::activeViewManager = manager;
    }

    void ViewManager::DismissViewManager(GorillaUI::Components::ViewManager* manager)
    {
        childViewManager = nullptr;
        manager->activeView->Deactivate();
        manager->Deactivate();
        activeView->Activate();
        ViewSystem::activeViewManager = this;
    }

    void ViewManager::ReplaceTopView(GorillaUI::Components::View* view)
    {
        if (activeView) activeView->Deactivate();
        activeView = view;
        Il2CppObject* viewTransform = activeView->transform();
        il2cpp_utils::RunMethod(viewTransform, "SetParent", transform());
        activeView->Activate();
    }

    void ViewManager::BackButtonWasPressed(GorillaUI::Components::View* view)
    {
        if (!parentViewManager) return;
        parentViewManager->DismissViewManager(this);
    }

    void ViewManager::PressButton(GorillaKeyboardButton* button)
    {
        if (activeView) 
            activeView->HandleInput(button->characterString);
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