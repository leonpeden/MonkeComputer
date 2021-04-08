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

#include "MonkeComputerConfigView.hpp"

#include "ViewLib/CustomComputer.hpp"
#include "Register.hpp"

#include "CustomQueues.hpp"
#include "GorillaUI/CustomQueueView.hpp"

#include "typedefs.h"
#include <vector>

#include "config.hpp"

#include "UnityEngine/GameObject.hpp"
#include "GlobalNamespace/GorillaComputer.hpp"

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
#define run(value...) CRASH_UNLESS(il2cpp_utils::RunMethod(value))

using namespace UnityEngine;
using namespace GlobalNamespace;

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
            
    INSTALL_HOOK_OFFSETLESS(getLogger(), GorillaComputer_Start, il2cpp_utils::FindMethodUnsafe("", "GorillaComputer", "Start", 0));
    INSTALL_HOOK_OFFSETLESS(getLogger(), GorillaComputer_CheckAutoBanList, il2cpp_utils::FindMethodUnsafe("", "GorillaComputer", "CheckAutoBanList", 1));
    INSTALL_HOOK_OFFSETLESS(getLogger(), GorillaComputer_BanMe, il2cpp_utils::FindMethodUnsafe("", "GorillaComputer", "BanMe", 2));
    
    using namespace GorillaUI::Components;
    custom_types::Register::RegisterTypes<CustomComputer, View, ViewManager, GorillaUI::Components::GorillaKeyboardButton>();
    custom_types::Register::RegisterTypes<ModSettingsViewManager, ModSettingsView, DetailView>();
    custom_types::Register::RegisterTypes<MainViewManager, MainView>();

    custom_types::Register::RegisterTypes<ColorChangeView, NameChangeView, CustomRoomView, TurnChangeView, MicChangeView, GroupChangeView, QueueChangeView>();
    custom_types::Register::RegisterTypes<BaseGameViewManager, BaseGameView>();

    custom_types::Register::RegisterType<CustomQueueView>();
    custom_types::Register::RegisterType<MonkeComputerConfigView>();
    GorillaUI::Register::RegisterViewManager<BaseGameViewManager*>("Game Settings", "1.0.4");
    GorillaUI::Register::RegisterViewManager<ModSettingsViewManager*>("Mod Settings", VERSION);
    GorillaUI::Register::RegisterView<DetailView*>("Details", VERSION);
    GorillaUI::Register::RegisterView<CustomQueueView*>("Custom Queues", VERSION);
    
    GorillaUI::Register::RegisterSettingsView<MonkeComputerConfigView*>("Monke Computer", VERSION);

    CustomQueues::add_queue("MODDED", "Modded", "  <size=40>A Queue for modded players, outside of the normal public lobbies.\n    You can't really report anyone for having a mod here, but griefing\n    is still prohibited.\n</size>");
    INFO("Mod Loaded!");
}