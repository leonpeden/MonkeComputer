#include "ViewLib/WatchActivatorTrigger.hpp"
#include "ViewLib/MonkeWatch.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector3.hpp"

#include "GlobalNamespace/GorillaTriggerColliderHandIndicator.hpp"
#include "GlobalNamespace/GorillaTagger.hpp"

DEFINE_TYPE(GorillaUI::Components::WatchActivatorTrigger);

using namespace UnityEngine;

extern Logger& getLogger();

namespace GorillaUI::Components
{
    void WatchActivatorTrigger::Awake()
    {
        getLogger().info("Activator Trigger component created!");

        get_gameObject()->set_layer(18);
        get_gameObject()->GetComponent<Collider*>()->set_isTrigger(true);
    }

    void WatchActivatorTrigger::Update()
    {
        if (MonkeWatch::get_instance()->isActive && !IsUpright()) MonkeWatch::get_instance()->SetActive(false);
    }

    void WatchActivatorTrigger::OnTriggerEnter(Collider* collider)
    {
        getLogger().info("Activator Trigger Triggered");

        if (MonkeWatch::get_instance()->isActive) return;
        if (!IsUpright()) return;
        
        GlobalNamespace::GorillaTriggerColliderHandIndicator* handIndicator = collider->GetComponentInParent<GlobalNamespace::GorillaTriggerColliderHandIndicator*>();
        if (handIndicator)
		{
            GlobalNamespace::GorillaTriggerColliderHandIndicator* component = collider->GetComponent<GlobalNamespace::GorillaTriggerColliderHandIndicator*>();

            MonkeWatch::get_instance()->SetActive(true);

			if (component)
			{
				GlobalNamespace::GorillaTagger* gorillaTagger = GlobalNamespace::GorillaTagger::get_Instance();
                bool isLeftHand = component->isLeftHand;
                float tapHapticStrength = gorillaTagger->tapHapticStrength;
                float tapHapticDuration = gorillaTagger->tapHapticDuration;
    
                gorillaTagger->StartVibration(isLeftHand, tapHapticStrength / 2.0f, tapHapticDuration);          
			}
		}
    }

    bool WatchActivatorTrigger::IsUpright()
    {
        // I know that this is not technically up, but because of how I need to make this button work it;s how we shall do things
        Vector3 up = -get_transform()->get_right();

        float dot = Vector3::Dot(up, Vector3::get_up());
        if (dot > 0.8f)
        {
            return true;
        }
        return false;
    }

}