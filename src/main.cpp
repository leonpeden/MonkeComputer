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

#include "typedefs.h"
#include <vector>

#include "config.hpp"

using namespace GorillaUI;
using namespace GorillaUI::Components;

ModInfo modInfo;

Logger& getLogger()
{
    static Logger *logger = new Logger(modInfo, LoggerOptions(false, true));
    return *logger;
}

#define INFO(value...) getLogger().info(value)
#define ERROR(value...) getLogger().error(value)
#define run(value...) CRASH_UNLESS(il2cpp_utils::RunMethod(value))

MAKE_HOOK_OFFSETLESS(GorillaComputer_Start, void, Il2CppObject* self)
{
    GorillaComputer_Start(self);

    Il2CppObject* computerGO = *il2cpp_utils::RunMethod(self, "get_gameObject");
    CustomComputer* computer = *il2cpp_utils::RunGenericMethod<CustomComputer*>(computerGO, "AddComponent", std::vector<Il2CppClass*>{classof(GorillaUI::CustomComputer*)});
    computer->Init(CreateView<MainView*>());
}

extern "C" void setup(ModInfo& info)
{
    info.id = ID;
    info.version = VERSION;
    modInfo = info;

    INFO("Setup!");
}

extern "C" void load()
{
    INFO("Loading mod...");
    if (!LoadConfig())
            SaveConfig();
            
    INSTALL_HOOK_OFFSETLESS(getLogger(), GorillaComputer_Start, il2cpp_utils::FindMethodUnsafe("", "GorillaComputer", "Start", 0));
    
    using namespace GorillaUI::Components;
    custom_types::Register::RegisterTypes<CustomComputer, View, ViewManager, GorillaKeyboardButton>();
    custom_types::Register::RegisterTypes<ModSettingsViewManager, ModSettingsView, DetailView>();
    custom_types::Register::RegisterTypes<MainViewManager, MainView>();

    custom_types::Register::RegisterTypes<ColorChangeView, NameChangeView, CustomRoomView, TurnChangeView, MicChangeView, GroupChangeView, QueueChangeView>();
    custom_types::Register::RegisterTypes<BaseGameViewManager, BaseGameView>();

    custom_types::Register::RegisterType<MonkeComputerConfigView>();
    GorillaUI::Register::RegisterViewManager<BaseGameViewManager*>("Game Settings", "1.0.3");
    GorillaUI::Register::RegisterViewManager<ModSettingsViewManager*>("Mod Settings", VERSION);
    GorillaUI::Register::RegisterView<DetailView*>("Details", VERSION);
    
    GorillaUI::Register::RegisterSettingsView<MonkeComputerConfigView*>("Monke Computer", "1.0.0");
    INFO("Mod Loaded!");
}