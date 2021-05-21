#include "ViewLib/MonkeWatch.hpp"
#include "ViewLib/MonkeWatchButton.hpp"
#include "ViewLib/WatchActivatorTrigger.hpp"

#include "GlobalNamespace/TransformFollow.hpp"
#include "UnityEngine/UI/Text.hpp"
#include "UnityEngine/Collider.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/PrimitiveType.hpp"
#include "UnityEngine/Renderer.hpp"
#include "UnityEngine/MeshFilter.hpp"

#include "BillboardedWatch.hpp"
#include "GorillaUI/MainViewManager.hpp"
#include "config.hpp"

#include "quest-cosmetic-loader/shared/CosmeticLoader.hpp"
DEFINE_TYPE(GorillaUI::MonkeWatch);

using namespace GorillaUI::Components;
using namespace UnityEngine;

namespace GorillaUI
{
    SafePtr<MonkeWatch> MonkeWatch::instance;
    void MonkeWatch::Init(View* initialView, GameObject* watchGO)
    {
        instance = this;
        activeViewManager = *il2cpp_utils::New<GorillaUI::MainViewManager*>();

        il2cpp_utils::SetFieldValue(activeViewManager, "mainView", initialView);

        activeViewManager->activeView = initialView;
        activeViewManager->Activate();
        
        screenInfo = CreateWatch(watchGO);

        SetupButtons();
        isActive = false;
    }

    void MonkeWatch::Init(View* initialView)
    {
        instance = this;
        activeViewManager = *il2cpp_utils::New<GorillaUI::MainViewManager*>();

        il2cpp_utils::SetFieldValue(activeViewManager, "mainView", initialView);

        activeViewManager->activeView = initialView;
        activeViewManager->Activate();
        
        screenInfo = CreateWatch();

        SetupButtons();
        isActive = false;
    }

    void MonkeWatch::Redraw()
    {
        instance->screenInfo.set_text(instance->activeViewManager->activeView->text);
    }

    MonkeWatch* MonkeWatch::get_instance()
    {
        return (MonkeWatch*)instance;
    }

    CustomScreenInfo MonkeWatch::CreateWatch(GameObject* watchGO)
    {
        
        Transform* watchTransform = watchGO->get_transform();
        
        // make the part with all the UI stuff actually rotate towards the player 
        watchTransform->Find(il2cpp_utils::createcsstr("Plane"))->get_gameObject()->AddComponent<BillboardedWatch*>();


        // make sure it's positioned right under the object that follows the player hand
        watchTransform->SetParent(get_transform());
        watchTransform->set_localPosition(Vector3::get_zero());
        watchTransform->set_localEulerAngles(Vector3(-90.0f, 90.0f, 0.0f));
        watchTransform->set_localScale(Vector3::get_one());

        WatchActivatorTrigger* activator = GameObject::CreatePrimitive(PrimitiveType::Cube)->AddComponent<WatchActivatorTrigger*>();
        
        Object::Destroy(activator->get_gameObject()->GetComponent<Renderer*>());
        Object::Destroy(activator->get_gameObject()->GetComponent<MeshFilter*>());

        GlobalNamespace::TransformFollow* follow = activator->get_gameObject()->AddComponent<GlobalNamespace::TransformFollow*>();
        follow->transformToFollow = get_transform();
        follow->offset  = Vector3(-0.04f, 0.0f, 0.0f);
        activator->get_transform()->set_localScale(Vector3(0.04f, 0.06f, 0.06f));
    
        CustomScreenInfo info;

        info.transform = watchTransform;
        info.text = watchTransform->Find(il2cpp_utils::createcsstr("Plane/Canvas"))->get_gameObject()->GetComponentInChildren<UnityEngine::UI::Text*>();
        info.renderer = watchTransform->Find(il2cpp_utils::createcsstr("Plane/Plane"))->get_gameObject()->GetComponent<UnityEngine::MeshRenderer*>();
        info.materials = info.renderer->get_materials();

        //info.set_color(config.screenColor);
        info.set_fontSize(80);

        return info;
    }

    CustomScreenInfo MonkeWatch::CreateWatch()
    {
        using namespace CosmeticsLoader;
        GameObject* watchGO = nullptr;
        std::string path = "/sdcard/ModData/com.AnotherAxiom.GorillaTag/Mods/MonkeComputer/Watch.package";
        auto* loader = new CosmeticLoader(path, [&](std::string name, Il2CppObject* obj){
            watchGO = (GameObject*)obj;
        }, "_Watch", il2cpp_utils::GetSystemType("UnityEngine", "GameObject"));
        
        return CreateWatch(watchGO);
    }

    void MonkeWatch::SetActive(bool value)
    {
        isActive = value;
        screenInfo.transform->Find(il2cpp_utils::createcsstr("Plane"))->get_gameObject()->SetActive(value);
    }

    void MonkeWatch::SetupButtons()
    {
        Transform* Buttons = screenInfo.transform->Find(il2cpp_utils::createcsstr("Plane/Buttons"));

        for (int i = 0; i < Buttons->get_childCount(); i++)
        {
            Transform* child = Buttons->GetChild(i);

            MonkeWatchButton* button = child->get_gameObject()->AddComponent<MonkeWatchButton*>();
            button->get_gameObject()->set_layer(18);
            button->get_gameObject()->GetComponent<Collider*>()->set_isTrigger(true);
            button->Init(this);
        }
    }

    void MonkeWatch::PressButton(GorillaUI::Components::MonkeWatchButton* button)
    {
        if (activeViewManager)
        {
            auto* notifyOfKeyPress = il2cpp_functions::class_get_method_from_name(il2cpp_utils::ExtractClass (activeViewManager), "NotifyOfKeyPress", 1);
            if (notifyOfKeyPress)
                il2cpp_utils::RunMethod(activeViewManager, notifyOfKeyPress, (int)button->key);
        }
    }
}