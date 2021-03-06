#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "beatsaber-hook/shared/utils/utils.h"
#include "beatsaber-hook/shared/utils/il2cpp-type-check.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"

#include "custom-types/shared/register.hpp"
#include "GorillaUI.hpp"
#include "GorillaUI/MainView.hpp"
#include "GorillaUI/MainViewManager.hpp"

#include "typedefs.h"
#include <vector>

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


void UseGorillaUI(Il2CppObject* self);

std::string dataDir = "";

MAKE_HOOK_OFFSETLESS(Player_Awake, void, Il2CppObject* self)
{
    Player_Awake(self);
    
    UseGorillaUI(self);
}

void UseGorillaUI(Il2CppObject* self)
{
    Vector3 euler = {0.0f, -90.0f, 0.0f};
    Vector3 pos = {-69.0f, 12.74f, -83.04f};
    
    //ViewSystem* viewSystem = CreateViewSystem(il2cpp_utils::GetClassFromName("GorillaUI", "MainViewManager"), pos, euler);
    ViewSystem* ViewSystem = CreateViewSystem<GorillaUI::MainViewManager*>(pos, euler);
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

    INSTALL_HOOK_OFFSETLESS(getLogger(), Player_Awake, il2cpp_utils::FindMethodUnsafe("GorillaLocomotion", "Player", "Awake", 0));
    
    using namespace GorillaUI::Components;
    custom_types::Register::RegisterType<Field>();
    custom_types::Register::RegisterType<InputField>();
    custom_types::Register::RegisterTypes<View, ViewManager, ViewSystem, GorillaKeyboardButton>();
    custom_types::Register::RegisterTypes<MainViewManager, MainView>();
    INFO("Mod Loaded!");
}