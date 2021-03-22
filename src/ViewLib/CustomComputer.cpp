#include "ViewLib/CustomComputer.hpp"
#include "Utils/TextUtils.hpp"
#include "KeyExtension.hpp"
#include "cosmeticsloader/shared/CosmeticLoader.hpp"
#include "GorillaUI/MainViewManager.hpp"
#include "config.hpp"

DEFINE_CLASS(GorillaUI::CustomComputer);
using namespace GorillaUI::Components;
using namespace TextUtils;
using namespace GorillaUI::KeyExtension;

extern Logger& getLogger();

namespace GorillaUI
{
    void CustomComputer::Init(GorillaUI::Components::View* initialView)
    {
        instance = this;
        activeViewManager = *il2cpp_utils::New<GorillaUI::MainViewManager*>();
        activeViewManager->computer = this;
        il2cpp_utils::SetFieldValue(activeViewManager, "mainView", initialView);
        activeViewManager->activeView = initialView;
        initialView->computer = this;
        activeViewManager->Activate();
        
        gorillaComputer = *il2cpp_utils::RunGenericMethod(this, "GetComponent", std::vector<Il2CppClass*>{il2cpp_utils::GetClassFromName("", "GorillaComputer")});
        il2cpp_utils::RunMethod(gorillaComputer, "set_enabled", false);


        Il2CppObject* transform = *il2cpp_utils::RunMethod(gorillaComputer, "get_transform");
        Il2CppObject* keyboardTransform = *il2cpp_utils::RunMethod(transform, "Find", il2cpp_utils::createcsstr("keyboard"));
        Il2CppObject* keyboardGO =  *il2cpp_utils::RunMethod(keyboardTransform, "get_gameObject");
        
        std::vector<Il2CppClass*> klass = {il2cpp_utils::GetClassFromName("UnityEngine", "MeshRenderer")};
        Il2CppObject* meshRenderer = *il2cpp_utils::RunGenericMethod(keyboardGO, "GetComponent", klass);
        Il2CppObject* material = *il2cpp_utils::RunMethod(meshRenderer, "get_material");
        Color kbColor = {0.0f, 0.0f, 0.0f};
        
        il2cpp_utils::RunMethod(material, "set_color", kbColor);
        ReplaceKeys(); 
        screenInfo = CreateMonitor();
    }

    void CustomComputer::Redraw()
    {
        instance->screenInfo.set_text(instance->activeViewManager->activeView->text);
    }

    CustomScreenInfo CustomComputer::CreateMonitor()
    {
        Il2CppObject* transform = *il2cpp_utils::RunMethod(this, "get_transform");
        Il2CppObject* monitor = *il2cpp_utils::RunMethod(transform, "Find", il2cpp_utils::createcsstr("monitor"));
        Il2CppObject* monitorGO = *il2cpp_utils::RunMethod(monitor, "get_gameObject");
        il2cpp_utils::RunMethod(monitorGO, "SetActive", false);
        
        using namespace CosmeticsLoader;
        Il2CppObject* newMonitor = nullptr;
        std::string path = "/sdcard/ModData/com.AnotherAxiom.GorillaTag/Mods/MonkeComputer/Monitor/monitor.json";
        auto* loader = new CosmeticLoader(path, [&](std::string name, Il2CppObject* obj){
            newMonitor = obj;
        }, "_Monitor", il2cpp_utils::GetSystemType("UnityEngine", "GameObject"));
        
        il2cpp_utils::RunMethod(newMonitor, "set_name", il2cpp_utils::createcsstr("Custom Monitor"));

        Vector3 localScale = {0.4f, 0.4f, 0.4f};
        Vector3 eulerAngles = {0.0f, 90.0f, 0.0f};
        Vector3 position = {-69.0f, 12.11f, -82.8f};

        Il2CppObject* newMonitorTransform = *il2cpp_utils::RunMethod(newMonitor, "get_transform");

        il2cpp_utils::RunMethod(newMonitorTransform, "set_localScale", localScale);
        il2cpp_utils::RunMethod(newMonitorTransform, "set_eulerAngles", eulerAngles);
        il2cpp_utils::RunMethod(newMonitorTransform, "set_position", position);

        CustomScreenInfo info;

        info.transform = newMonitorTransform;
        info.text = *il2cpp_utils::RunGenericMethod(newMonitor, "GetComponentInChildren", std::vector<Il2CppClass*>{il2cpp_utils::GetClassFromName("UnityEngine.UI", "Text")});
        info.renderer = *il2cpp_utils::RunGenericMethod(newMonitor, "GetComponentInChildren", std::vector<Il2CppClass*>{il2cpp_utils::GetClassFromName("UnityEngine", "MeshRenderer")});
        info.materials = *il2cpp_utils::RunMethod<Array<Il2CppObject*>*>(info.renderer, "get_materials");

        info.set_color(config.screenColor);
        info.set_fontSize(80);
        
        return info;
    }

    void CustomComputer::SetBG(float r, float g, float b)
    {
        screenInfo.set_color({r, g, b});
        config.screenColor = {r, g, b};
        SaveConfig();
    }
    
    void CustomComputer::ReplaceKeys()
    {
        keys.clear();

        // hijack the original keys
        Array<Il2CppObject*>* buttons = *il2cpp_utils::RunGenericMethod<Array<Il2CppObject*>*>(this, "GetComponentsInChildren", std::vector<Il2CppClass*>{il2cpp_utils::GetClassFromName("", "GorillaKeyboardButton")});
        int length = buttons->Length();
        for (int i = 0; i < length; i++)
        {
            Il2CppObject* button = buttons->values[i];
            Il2CppString* characterString = *il2cpp_utils::GetFieldValue<Il2CppString*>(button, "characterString");
            std::string cppString = to_utf8(csstrtostr(characterString));
            cppString = toLower(cppString);
            EKeyboardKey key;
            if (!NameToKey(cppString, key)) continue;
            Il2CppObject* gameObject = *il2cpp_utils::RunMethod(button, "get_gameObject");
            GorillaKeyboardButton* customButton = *il2cpp_utils::RunGenericMethod<GorillaKeyboardButton*>(gameObject, "AddComponent", std::vector<Il2CppClass*>{classof(GorillaKeyboardButton*)});

            float pressTime = *il2cpp_utils::GetFieldValue<float>(button, "pressTime");
            bool functionKey = *il2cpp_utils::GetFieldValue<bool>(button, "functionKey");
            Array<float>* sliderValues = *il2cpp_utils::GetFieldValue<Array<float>*>(button, "sliderValues");
            
            il2cpp_utils::SetFieldValue(customButton, "pressTime", pressTime);
            il2cpp_utils::SetFieldValue(customButton, "functionKey", functionKey);
            il2cpp_utils::SetFieldValue(customButton, "sliderValues", sliderValues);

            il2cpp_utils::RunMethod("UnityEngine", "Object", "DestroyImmediate", button);
            
            customButton->Init(this, key);
            keys[key] = customButton;
        }

        auto* enterKey = keys.at(EKeyboardKey::Enter);
        auto* mKey = keys.at(EKeyboardKey::M);
        auto* deleteKey = keys.at(EKeyboardKey::Delete);

        Il2CppObject* enterGO = *il2cpp_utils::RunMethod(enterKey, "get_gameObject");
        Il2CppObject* deleteGO = *il2cpp_utils::RunMethod(deleteKey, "get_gameObject");
        Vector3 spaceOffset = {2.6f, 0.0f, 3.0f};
        Vector3 deleteOffset = {2.3f, 0.0f, 0.0f};
        
        CreateKey(enterGO, "Space", spaceOffset, EKeyboardKey::Space, "SPACE");
        CreateKey(deleteGO, "Delete", deleteOffset, EKeyboardKey::Delete);

        Color backButtonColor = {0.52f, 0.52f, 0.87f};

        deleteKey->Init(this, EKeyboardKey::Back, "BACK", backButtonColor);

        Color arrowKeyButtonColor = {0.67f, 0.86f, 0.67f};

        Vector3 leftKeyOffset = {0.0f, 0.0f, 5.6f};
        Vector3 rightKeyOffset = {0.0f, 0.0f, 10.2f};
        Vector3 upKeyOffset = {-2.3f, 0.0f, 7.9f};
        Vector3 downKeyOffset = {0.0f, 0.0f, 7.9f};

        // make arrow keys
        Il2CppObject* mKeyGO = *il2cpp_utils::RunMethod(mKey, "get_gameObject");

        Il2CppObject* mKeyT = *il2cpp_utils::RunMethod(mKey, "get_transform");
        
        CreateKey(mKeyGO, "Left", leftKeyOffset, EKeyboardKey::Left, "<", arrowKeyButtonColor);
        CreateKey(mKeyGO, "Down", downKeyOffset, EKeyboardKey::Down, "v", arrowKeyButtonColor);
        CreateKey(mKeyGO, "Right", rightKeyOffset, EKeyboardKey::Right, ">", arrowKeyButtonColor);
        CreateKey(mKeyGO, "Up", upKeyOffset, EKeyboardKey::Up, "^", arrowKeyButtonColor);
    }

    GorillaUI::Components::GorillaKeyboardButton* CustomComputer::CreateKeyNoInit(Il2CppObject* prefab, std::string goName, Vector3 offset, EKeyboardKey key)
    {
        // make sure it's a GO
        Il2CppObject* go = *il2cpp_utils::RunMethod(prefab, "get_gameObject");

        // get transform
        Il2CppObject* prefabTransform = *il2cpp_utils::RunMethod(go, "get_transform");
        Il2CppObject* prefabParent = *il2cpp_utils::RunMethod(prefabTransform, "get_parent");
        
        //duplicate prefab GO
        Il2CppObject* newKey = *il2cpp_utils::RunMethod("UnityEngine", "Object", "Instantiate", prefab);
        
        // get transform
        Il2CppObject* newKeyTransform = *il2cpp_utils::RunMethod(newKey, "get_transform");
        
        // set parent to prefab parent
        il2cpp_utils::RunMethod(newKeyTransform, "SetParent", prefabParent, false);

        // re get transform so it's definitely tthe right one
        newKeyTransform = *il2cpp_utils::RunMethod(newKey, "get_transform");

        // get localpos
        Vector3 pos = *il2cpp_utils::RunMethod<Vector3>(newKeyTransform, "get_localPosition");

        // update local pos
        pos.x += offset.x;
        pos.y += offset.y;
        pos.z += offset.z;

        // set local pos
        il2cpp_utils::RunMethod(newKeyTransform, "set_localPosition", pos);
        
        // get pos
        pos = *il2cpp_utils::RunMethod<Vector3>(newKeyTransform, "get_position");
        
        // set name
        il2cpp_utils::RunMethod(newKey, "set_name", il2cpp_utils::createcsstr(goName));
        
        // add custom key component
        static std::vector<Il2CppClass*> klass = {classof(GorillaUI::Components::GorillaKeyboardButton*)};
        GorillaKeyboardButton* customKeyboardKey = *il2cpp_utils::RunGenericMethod<GorillaKeyboardButton*>(newKey, "GetComponent", klass);

        return customKeyboardKey;
    }

    GorillaUI::Components::GorillaKeyboardButton* CustomComputer::CreateKey(Il2CppObject* prefab, std::string goName, Vector3 Offset, EKeyboardKey key)
    {
        GorillaKeyboardButton* customKeyboardKey = CreateKeyNoInit(prefab, goName, Offset, key);
        customKeyboardKey->Init(this, key);
        return customKeyboardKey;
    }

    GorillaUI::Components::GorillaKeyboardButton* CustomComputer::CreateKey(Il2CppObject* prefab, std::string goName, Vector3 Offset, EKeyboardKey key, std::string label)
    {
        GorillaKeyboardButton* customKeyboardKey = CreateKeyNoInit(prefab, goName, Offset, key);
        customKeyboardKey->Init(this, key, label);
        return customKeyboardKey;
    }

    GorillaUI::Components::GorillaKeyboardButton* CustomComputer::CreateKey(Il2CppObject* prefab, std::string goName, Vector3 Offset, EKeyboardKey key, std::string label, Color color)
    {
        GorillaKeyboardButton* customKeyboardKey = CreateKeyNoInit(prefab, goName, Offset, key);
        customKeyboardKey->Init(this, key, label, color);
        return customKeyboardKey;
    }

    void CustomComputer::PressButton(GorillaKeyboardButton* button)
    {
        if (activeViewManager) 
        {
            auto* notifyOfKeyPress = il2cpp_functions::class_get_method_from_name(il2cpp_utils::ExtractClass (activeViewManager), "NotifyOfKeyPress", 1);
            if (notifyOfKeyPress)
                il2cpp_utils::RunMethod(activeViewManager, notifyOfKeyPress, (int)button->key);
        }
    }

    CustomComputer* CustomComputer::get_instance()
    {
        return instance;
    }

}