#include "GorillaUI/MainView.hpp"
#include "GorillaUI.hpp"

DEFINE_CLASS(GorillaUI::MainView);

extern Logger& getLogger();

namespace GorillaUI
{
    void MainView::DidActivate(bool firstActivation)
    {
        if (firstActivation)
        {
            Il2CppObject* transform = *il2cpp_utils::RunMethod(this, "get_transform");
            CreateText(transform, "Hello World!");
            getLogger().info("Main View Manager says hello!");
        }
    }
}