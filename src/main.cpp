#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "beatsaber-hook/shared/utils/utils.h"
#include "beatsaber-hook/shared/utils/il2cpp-type-check.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"

#include "custom-types/shared/register.hpp"
#include "GorillaUI.hpp"
#include "GorillaUI/DetailView.hpp"
#include "GorillaUI/MainView.hpp"
#include "GorillaUI/MainWatchView.hpp"
#include "GorillaUI/MainViewManager.hpp"
#include "GorillaUI/ModSettingsView/ModSettingsView.hpp"
#include "GorillaUI/ModSettingsView/ModSettingsViewManager.hpp"

#include "GorillaUI/BaseGameViews/BaseGameViewManager.hpp"
#include "GorillaUI/BaseGameViews/BaseGameView.hpp"
#include "GorillaUI/BaseGameViews/ColorChangeView.hpp"
#include "GorillaUI/BaseGameViews/CustomRoomView.hpp"
#include "GorillaUI/BaseGameViews/TurnChangeView.hpp"
#include "GorillaUI/BaseGameViews/NameChangeView.hpp"
#include "GorillaUI/BaseGameViews/QueueChangeView.hpp"
#include "GorillaUI/BaseGameViews/MicChangeView.hpp"
#include "GorillaUI/BaseGameViews/GroupChangeView.hpp"
#include "GorillaUI/BaseGameViews/VoiceChatView.hpp"

#include "MonkeComputerConfigView.hpp"

#include "ViewLib/CustomComputer.hpp"
#include "ViewLib/MonkeWatch.hpp"
#include "ViewLib/MonkeWatchButton.hpp"
#include "ViewLib/WatchActivatorTrigger.hpp"

#include "Register.hpp"

#include "BillboardedWatch.hpp"
#include "CustomQueues.hpp"
#include "GorillaUI/CustomQueueView.hpp"

#include "typedefs.h"
#include <vector>

#include "config.hpp"

#include "UnityEngine/GameObject.hpp"
#include "GlobalNamespace/GorillaComputer.hpp"
#include "GorillaLocomotion/Player.hpp"
#include "PlayFab/PlayFabError.hpp"
#include "System/Collections/Generic/Dictionary_2.hpp"
#include "System/Collections/Generic/KeyValuePair_2.hpp"
#include "System/DateTime.hpp"
#include "System/TimeSpan.hpp"

#include "GlobalNamespace/PlayFabAuthenticator.hpp"
#include "GlobalNamespace/TransformFollow.hpp"

#include "CustomBackgrounds/BackgroundsList.hpp"
#include "CustomBackgrounds/BackgroundsView.hpp"

#include "BanManager.hpp"

using namespace GorillaUI;
using namespace GorillaUI::Components;

ModInfo modInfo = {ID, VERSION};

Logger& getLogger()
{
    static Logger *logger = new Logger(modInfo, LoggerOptions(false, true));
    return *logger;
}

#define INFO(value...) getLogger().info(value)
#define ERROR(value...) getLogger().error(value)

using namespace UnityEngine;
using namespace GlobalNamespace;
using namespace GorillaLocomotion;

MAKE_HOOK_OFFSETLESS(Player_Awake, void, Player* self)
{
    Player_Awake(self);
    return;

    GameObject* watchObj = GameObject::New_ctor();
    GlobalNamespace::TransformFollow* follow = watchObj->AddComponent<GlobalNamespace::TransformFollow*>();
    watchObj->set_layer(18);
    Transform* leftHand = self->get_transform()->Find(il2cpp_utils::createcsstr("TurnParent/LeftHand Controller"));
    follow->transformToFollow = leftHand;

    follow->offset = Vector3(-0.025f, -0.025f , -0.1f);
    watchObj->get_transform()->set_localScale(Vector3::get_one() *.2f);

    MonkeWatch* watch = watchObj->AddComponent<MonkeWatch*>();
    watch->Init(CreateView<MainWatchView*>());
    watch->SetActive(true);
}

MAKE_HOOK_OFFSETLESS(GorillaComputer_Start, void, GorillaComputer* self)
{
    GorillaComputer_Start(self);
    
    GameObject* computerGO = self->get_gameObject();
    CustomComputer* computer = computerGO->AddComponent<CustomComputer*>();
    computer->Init(CreateView<MainView*>());
}

MAKE_HOOK_OFFSETLESS(GorillaComputer_CheckAutoBanList, bool, GorillaComputer* self, Il2CppString* nameToCheck)
{   
    INFO("Anywhere Two Week Ban List: ");
    for (int i = 0; i < self->anywhereTwoWeek->Length(); i++)
    {
        std::string name = to_utf8(csstrtostr(self->anywhereTwoWeek->values[i]));
        INFO("\t%s", name.c_str());
    }

    INFO("Anywhere One Week Ban List: ");
    for (int i = 0; i < self->anywhereOneWeek->Length(); i++)
    {
        std::string name = to_utf8(csstrtostr(self->anywhereOneWeek->values[i]));
        INFO("\t%s", name.c_str());
    }

    INFO("Exact One Week Ban List: ");
    for (int i = 0; i < self->exactOneWeek->Length(); i++)
    {
        std::string name = to_utf8(csstrtostr(self->exactOneWeek->values[i]));
        INFO("\t%s", name.c_str());
    }

    return GorillaComputer_CheckAutoBanList(self, nameToCheck);
}

MAKE_HOOK_OFFSETLESS(GorillaComputer_BanMe, void, GorillaComputer* self, int hours, Il2CppString* nameToCheck)
{
    std::string name = to_utf8(csstrtostr(nameToCheck));
    INFO("Player Tried setting name %s, but a ban of %d hours was prevented", name.c_str(), hours);
}

MAKE_HOOK_OFFSETLESS(PlayFabAuthenticator_OnPlayFabError, void, GlobalNamespace::PlayFabAuthenticator* self, PlayFab::PlayFabError* obj)
{
    if (!obj || !obj->ErrorMessage) 
    {
        PlayFabAuthenticator_OnPlayFabError(self, obj);
        return;
    }
    std::string error = to_utf8(csstrtostr(obj->ErrorMessage));

    using DetailsEnumerator = System::Collections::Generic::Dictionary_2<Il2CppString*, System::Collections::Generic::List_1<Il2CppString*>*>::Enumerator;
    using Details = System::Collections::Generic::KeyValuePair_2<Il2CppString*, List<Il2CppString*>*>;
    using namespace System;
    
    bool isBanned = false;
    std::string DisplayedMessage = "";
    
    // normal ban
    if (error == "The account making this request is currently banned")
    {
        isBanned = true;

        // C# enumeration, kinda weird innit
        DetailsEnumerator enumerator = obj->ErrorDetails->GetEnumerator();
        if (enumerator.MoveNext())
        {
            Details pair = enumerator.get_Current();
            Il2CppString* firstCS = pair.get_Value()->items->values[0];
            std::string first = firstCS ? to_utf8(csstrtostr(firstCS)) : "";
            std::string reason = to_utf8(csstrtostr(pair.get_Key()));

            // if not indefinite, so it will expirre within about 2 weeks
            if (first != "Indefinite")
            {   

                DateTime end = DateTime::Parse(firstCS); 
                TimeSpan time = end - DateTime::get_UtcNow();

                int count = time.get_TotalHours() + 1;

                DisplayedMessage += "You have been banned. You will not be able to play until the ban expires.\nReason: ";
                DisplayedMessage += reason;
                DisplayedMessage += string_format("\nHours Left: %d", count);
            }
            // infinte ban, this is so sad, alexa play despacito
            else
            {
                DisplayedMessage += "You have been banned Indefinitely.\nReason: ";
                DisplayedMessage += reason;
            }
        }
    }
    // ip ban
    else if (error == "The IP making this request is currently banned")
    {
        isBanned = true;
        DisplayedMessage = "<size=40>\nYour IP has been banned,\n due to the possibility of ban evasion nobody else\n from this IP will be able to connect until the ban expires.\n Only the banned user can be shown the reason and ban duration.\n</size>";
    }

    if (isBanned)
    {
        BanManager::set_displayMessage(DisplayedMessage);
        
        std::vector<ModEntry>& entries = Register::get_entries();
        
        for (auto& entry : entries)
        {
            if (entry.get_info().id == "Details")
            {
                CustomComputer* pc = CustomComputer::get_instance();
                if (pc)
                    pc->activeViewManager->ReplaceTopView(entry.get_view());
                break;
            }
        }
    }
    PlayFabAuthenticator_OnPlayFabError(self, obj);
}


extern "C" void setup(ModInfo& info)
{
    info.id = ID;
    info.version = VERSION;
}

void loadlib()
{
    INFO("Loading mod...");
    if (!LoadConfig())
            SaveConfig();
    BackgroundsList::Load();
    INSTALL_HOOK_OFFSETLESS(getLogger(), GorillaComputer_Start, il2cpp_utils::FindMethodUnsafe("", "GorillaComputer", "Start", 0));
    INSTALL_HOOK_OFFSETLESS(getLogger(), GorillaComputer_CheckAutoBanList, il2cpp_utils::FindMethodUnsafe("", "GorillaComputer", "CheckAutoBanList", 1));
    INSTALL_HOOK_OFFSETLESS(getLogger(), GorillaComputer_BanMe, il2cpp_utils::FindMethodUnsafe("", "GorillaComputer", "BanMe", 2));
    INSTALL_HOOK_OFFSETLESS(getLogger(), Player_Awake, il2cpp_utils::FindMethodUnsafe("GorillaLocomotion", "Player", "Awake", 0));
    INSTALL_HOOK_OFFSETLESS(getLogger(), PlayFabAuthenticator_OnPlayFabError, il2cpp_utils::FindMethodUnsafe("", "PlayFabAuthenticator", "OnPlayFabError", 1));
    
    using namespace GorillaUI::Components;
    custom_types::Register::RegisterTypes<CustomComputer, MonkeWatch, View, ViewManager, GorillaUI::Components::GorillaKeyboardButton, MonkeWatchButton, WatchActivatorTrigger, BillboardedWatch>();
    custom_types::Register::RegisterTypes<ModSettingsViewManager, ModSettingsView, DetailView>();
    custom_types::Register::RegisterTypes<MainViewManager, MainView, MainWatchView>();

    custom_types::Register::RegisterTypes<ColorChangeView, NameChangeView, CustomRoomView, TurnChangeView, MicChangeView, GroupChangeView, QueueChangeView, VoiceChatView>();
    custom_types::Register::RegisterTypes<BaseGameViewManager, BaseGameView>();

    custom_types::Register::RegisterType<CustomQueueView>();
    custom_types::Register::RegisterType<MonkeComputerConfigView>();
    custom_types::Register::RegisterType<BackgroundsView>();

    GorillaUI::Register::RegisterViewManager<BaseGameViewManager*>("Game Settings", "1.0.4");
    GorillaUI::Register::RegisterViewManager<ModSettingsViewManager*>("Mod Settings", VERSION);
    GorillaUI::Register::RegisterView<DetailView*>("Details", VERSION);
    GorillaUI::Register::RegisterView<CustomQueueView*>("Custom Queues", VERSION);
    
    GorillaUI::Register::RegisterSettingsView<MonkeComputerConfigView*>("Monke Computer", VERSION);
    GorillaUI::Register::RegisterSettingsView<BackgroundsView*>("Custom Backgrounds", VERSION);

    CustomQueues::add_queue("MODDED", "Modded", "  <size=40>A Queue for modded players, outside of the normal public lobbies.\n    You can't really report anyone for having a mod here, but griefing\n    is still prohibited.\n</size>");
    INFO("Mod Loaded!");
}