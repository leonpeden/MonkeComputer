#include "Components/GorillaKeyboardButton.hpp"
#include "Components/ViewSystem.hpp"
#include "Components/ViewManager.hpp"

DEFINE_CLASS(GorillaUI::Components::GorillaKeyboardButton);

namespace GorillaUI::Components
{
    void GorillaKeyboardButton::OnTriggerEnter(Il2CppObject* collider)
    {
        Il2CppObject* handIndicator = CRASH_UNLESS(il2cpp_utils::RunGenericMethod(collider, "GetComponentInParent", std::vector<Il2CppClass*>{il2cpp_utils::GetClassFromName("", "GorillaTriggerColliderHandIndicator")}));
        if (handIndicator)
		{
			Il2CppObject* component = CRASH_UNLESS(il2cpp_utils::RunGenericMethod(collider, "GetComponent", std::vector<Il2CppClass*>{il2cpp_utils::GetClassFromName("", "GorillaTriggerColliderHandIndicator")}));

			ViewSystem::activeViewManager->PressButton(this);
			if (component)
			{
				Il2CppObject* gorillaTagger = CRASH_UNLESS(il2cpp_utils::RunMethod("", "GorillaTagger", "get_Instance"));
                bool isLeftHand = CRASH_UNLESS(il2cpp_utils::GetFieldValue<bool>(component, "isLeftHand"));
                float tapHapticStrength = CRASH_UNLESS(il2cpp_utils::GetFieldValue<float>(gorillaTagger, "tapHapticStrength"));
                float tapHapticDuration = CRASH_UNLESS(il2cpp_utils::GetFieldValue<float>(gorillaTagger, "tapHapticDuration"));
    
                CRASH_UNLESS(il2cpp_utils::RunMethod(gorillaTagger, "StartVibration", isLeftHand, tapHapticStrength / 2.0f, tapHapticDuration));          
			}
		}
    }
}