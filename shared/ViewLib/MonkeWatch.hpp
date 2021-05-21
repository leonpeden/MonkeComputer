#pragma once

#include "custom-types/shared/macros.hpp"
#include "beatsaber-hook/shared/utils/typedefs-wrappers.hpp"

#include "../ViewLib/CustomScreenInfo.hpp"
#include "../ViewLib/ViewManager.hpp"
#include "../ViewLib/View.hpp"

#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/GameObject.hpp"

namespace GorillaUI::Components
{
    class MonkeWatchButton;
}


DECLARE_CLASS_CODEGEN(GorillaUI, MonkeWatch, UnityEngine::MonoBehaviour, 
    DECLARE_METHOD(static void, Redraw);
    DECLARE_METHOD(static MonkeWatch*, get_instance);
    DECLARE_METHOD(void, SetupButtons);
    DECLARE_METHOD(void, SetActive, bool value);
    DECLARE_METHOD(void, PressButton, GorillaUI::Components::MonkeWatchButton* button);
    DECLARE_INSTANCE_FIELD(bool, isActive);
    public:
        GorillaUI::Components::ViewManager* activeViewManager = nullptr;
        void Init(GorillaUI::Components::View* initialView, UnityEngine::GameObject* watchGO);
        void Init(GorillaUI::Components::View* initialView);
    private:
        CustomScreenInfo screenInfo;
        static SafePtr<MonkeWatch> instance;
        CustomScreenInfo CreateWatch();
        CustomScreenInfo CreateWatch(UnityEngine::GameObject* watchGO);
    REGISTER_FUNCTION(
            REGISTER_METHOD(Redraw);
            REGISTER_METHOD(get_instance);
            REGISTER_METHOD(SetupButtons);
            REGISTER_METHOD(SetActive);
            REGISTER_FIELD(isActive);
    )
)