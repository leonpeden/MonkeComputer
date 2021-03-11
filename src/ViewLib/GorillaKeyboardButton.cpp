#include "ViewLib/GorillaKeyboardButton.hpp"
#include "ViewLib/ViewManager.hpp"
#include <thread>

DEFINE_CLASS(GorillaUI::Components::GorillaKeyboardButton);

#define KEY_BUMP_AMOUNT 0.2f
#define PRESS_COOLDOWN 150

static const Color pressedColor = {0.5f, 0.5f, 0.5f};

extern Logger& getLogger();

namespace GorillaUI::Components
{
    void GorillaKeyboardButton::Awake()
    {
        il2cpp_utils::RunMethod(this, "set_enabled", false);
        Il2CppObject* meshRenderer = *il2cpp_utils::RunGenericMethod(this, "GetComponent", std::vector<Il2CppClass*>{il2cpp_utils::GetClassFromName("UnityEngine", "MeshRenderer")});
        material = *il2cpp_utils::RunMethod(meshRenderer, "get_material");
    
        originalColor = *il2cpp_utils::RunMethod<Color>(material, "get_color");
    }

    void GorillaKeyboardButton::Init(GorillaUI::CustomComputer* computer, EKeyboardKey key)
    {
        this->computer = computer;
        this->key = key;
        il2cpp_utils::RunMethod(this, "set_enabled", true);
    }

    void GorillaKeyboardButton::Init(GorillaUI::CustomComputer* computer, EKeyboardKey key, std::string text)
    {
        this->Init(computer, key);

        Il2CppObject* go = *il2cpp_utils::RunMethod(this, "get_gameObject");
        Il2CppObject* textComponent = *il2cpp_utils::RunGenericMethod(go, "GetComponentInChildren", std::vector<Il2CppClass*>{il2cpp_utils::GetClassFromName("UnityEngine.UI", "Text")});
        il2cpp_utils::RunMethod(textComponent, "set_text", il2cpp_utils::createcsstr(text));
    }

    void GorillaKeyboardButton::Init(GorillaUI::CustomComputer* computer, EKeyboardKey key, std::string text, Color buttonColor)
    {
        Init(computer, key, text);

        originalColor = buttonColor;
        il2cpp_utils::RunMethod(material, "set_color", originalColor);
    }


    void GorillaKeyboardButton::BumpIn()
    {
        Il2CppObject* transform = *il2cpp_utils::RunMethod(this, "get_transform");
        Vector3 pos = *il2cpp_utils::RunMethod<Vector3>(transform, "get_localPosition");
        pos.y -= KEY_BUMP_AMOUNT;
        il2cpp_utils::RunMethod(transform, "set_localPosition", pos);
        il2cpp_utils::RunMethod(material, "set_color", pressedColor);
    }

    void GorillaKeyboardButton::BumpOut()
    {
        Il2CppObject* transform = *il2cpp_utils::RunMethod(this, "get_transform");
        Vector3 pos = *il2cpp_utils::RunMethod<Vector3>(transform, "get_localPosition");
        pos.y += KEY_BUMP_AMOUNT;
        il2cpp_utils::RunMethod(transform, "set_localPosition", pos);
        il2cpp_utils::RunMethod(material, "set_color", originalColor);
    }

    void GorillaKeyboardButton::OnTriggerEnter(Il2CppObject* collider)
    {
        BumpIn();
        if (isOnCooldown) return;
        isOnCooldown = true;
        Il2CppObject* handIndicator = CRASH_UNLESS(il2cpp_utils::RunGenericMethod(collider, "GetComponentInParent", std::vector<Il2CppClass*>{il2cpp_utils::GetClassFromName("", "GorillaTriggerColliderHandIndicator")}));
        if (handIndicator)
		{
			Il2CppObject* component = CRASH_UNLESS(il2cpp_utils::RunGenericMethod(collider, "GetComponent", std::vector<Il2CppClass*>{il2cpp_utils::GetClassFromName("", "GorillaTriggerColliderHandIndicator")}));

			computer->PressButton(this);
			if (component)
			{
				Il2CppObject* gorillaTagger = CRASH_UNLESS(il2cpp_utils::RunMethod("", "GorillaTagger", "get_Instance"));
                bool isLeftHand = CRASH_UNLESS(il2cpp_utils::GetFieldValue<bool>(component, "isLeftHand"));
                float tapHapticStrength = CRASH_UNLESS(il2cpp_utils::GetFieldValue<float>(gorillaTagger, "tapHapticStrength"));
                float tapHapticDuration = CRASH_UNLESS(il2cpp_utils::GetFieldValue<float>(gorillaTagger, "tapHapticDuration"));
    
                CRASH_UNLESS(il2cpp_utils::RunMethod(gorillaTagger, "StartVibration", isLeftHand, tapHapticStrength / 2.0f, tapHapticDuration));          
			}
		}

        std::thread cooldown([&]{
            for (int i = 0; i < PRESS_COOLDOWN; i++) usleep(1000);
            isOnCooldown = false;
        });

        cooldown.detach();
    }

    void GorillaKeyboardButton::OnTriggerExit(Il2CppObject* collider)
    {
        BumpOut();
    }
}