#include "ViewLib/ViewManager.hpp"
#include "KeyExtension.hpp"
#include "typedefs.h"
#include "ViewLib/CustomComputer.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"

DEFINE_TYPE(GorillaUI::Components::ViewManager);

extern Logger& getLogger();

using namespace UnityEngine;

namespace GorillaUI::Components
{
    void ViewManager::Activate()
    {
        auto* didActivate = il2cpp_functions::class_get_method_from_name(il2cpp_utils::ExtractClass (this), "DidActivate", 1);
        if (didActivate)
            il2cpp_utils::RunMethod(this, didActivate, !activatedBefore);

        if (activeView)
        {
            activeView->computer = computer;
            activeView->Activate();
        }
        activatedBefore = true;
    }

    void ViewManager::Deactivate()
    {
        auto* didDeactivate = il2cpp_functions::class_get_method_from_name(il2cpp_utils::ExtractClass (this), "DidDeactivate", 0);
        if (didDeactivate)
            il2cpp_utils::RunMethod(this, didDeactivate);
    }
    
    void ViewManager::PresentViewManager(GorillaUI::Components::ViewManager* manager)
    {
        childViewManager = manager;
        manager->parentViewManager = this;
        manager->computer = computer;
        activeView->Deactivate();
        manager->Activate();
        computer->activeViewManager = manager;
    }

    void ViewManager::DismissViewManager(GorillaUI::Components::ViewManager* manager)
    {
        childViewManager = nullptr;
        manager->activeView->Deactivate();
        manager->Deactivate();
        activeView->Activate();
        computer->activeViewManager = this;
        CustomComputer::Redraw();
    }

    void ViewManager::ReplaceTopView(GorillaUI::Components::View* view)
    {
        if (activeView) activeView->Deactivate();
        view->computer = computer;
        activeView = view;
        activeView->Activate();
        CustomComputer::Redraw();
    }
}