#include "ViewLib/MonkeWatchButton.hpp"
#include "ViewLib/ViewManager.hpp"
#include "KeyExtension.hpp"

#include <thread>

#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/Text.hpp"

#include "GlobalNamespace/GorillaTriggerColliderHandIndicator.hpp"
#include "GlobalNamespace/GorillaTagger.hpp"

DEFINE_TYPE(GorillaUI::Components::MonkeWatchButton);

#define KEY_BUMP_AMOUNT 0.05f
#define PRESS_COOLDOWN 150

using namespace UnityEngine;
static const UnityEngine::Color pressedColor = {0.5f, 0.5f, 0.5f};

extern Logger& getLogger();

namespace GorillaUI::Components
{
    void MonkeWatchButton::Awake()
    {
        set_enabled(false);
        MeshRenderer* meshRenderer = this->GetComponent<MeshRenderer*>();
        material = meshRenderer->get_material();
        originalColor = material->get_color();
    }

    void MonkeWatchButton::Init(GorillaUI::MonkeWatch* watch)
    {
        this->watch = watch;
        
        Il2CppString* nameCS = get_gameObject()->get_name();
        std::string name = to_utf8(csstrtostr(nameCS));

        KeyExtension::NameToKey(name, key);

        set_enabled(true);
    }

    void MonkeWatchButton::BumpIn()
    {
        Vector3 pos = get_transform()->get_localPosition();
        pos.z -= KEY_BUMP_AMOUNT;
        get_transform()->set_localPosition(pos);
        material->set_color(pressedColor);
    }

    void MonkeWatchButton::BumpOut()
    {
        Vector3 pos = get_transform()->get_localPosition();
        pos.z += KEY_BUMP_AMOUNT;
        get_transform()->set_localPosition(pos);
        material->set_color(originalColor);
    }

    void MonkeWatchButton::OnTriggerEnter(Collider* collider)
    {
        BumpIn();
        if (isOnCooldown) return;
        isOnCooldown = true;
        
        GlobalNamespace::GorillaTriggerColliderHandIndicator* handIndicator = collider->GetComponentInParent<GlobalNamespace::GorillaTriggerColliderHandIndicator*>();
        if (handIndicator)
		{
            GlobalNamespace::GorillaTriggerColliderHandIndicator* component = collider->GetComponent<GlobalNamespace::GorillaTriggerColliderHandIndicator*>();

			watch->PressButton(this);
			if (component)
			{
				GlobalNamespace::GorillaTagger* gorillaTagger = GlobalNamespace::GorillaTagger::get_Instance();
                bool isLeftHand = component->isLeftHand;
                float tapHapticStrength = gorillaTagger->tapHapticStrength;
                float tapHapticDuration = gorillaTagger->tapHapticDuration;
    
                gorillaTagger->StartVibration(isLeftHand, tapHapticStrength / 2.0f, tapHapticDuration);          
			}
		}

        std::thread cooldown([&]{
            for (int i = 0; i < PRESS_COOLDOWN; i++) usleep(1000);
            isOnCooldown = false;
        });

        cooldown.detach();
    }

    void MonkeWatchButton::OnTriggerExit(Collider* collider)
    {
        BumpOut();
    }
}