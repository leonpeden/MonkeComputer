#include "config.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "beatsaber-hook/shared/rapidjson/include/rapidjson/document.h"

static ModInfo modInfo = {ID, VERSION};
extern Logger& getLogger();

config_t config;
Configuration& getConfig()
{
    static Configuration config(modInfo);
    config.Load();
    return config;
}

void SaveScreenColor(rapidjson::Document::AllocatorType& allocator, ConfigDocument& configDoc)
{
    rapidjson::Value colorVal;
    colorVal.SetObject();
    colorVal.AddMember("r", config.screenColor.r, allocator);
    colorVal.AddMember("g", config.screenColor.g, allocator);
    colorVal.AddMember("b", config.screenColor.b, allocator);
    configDoc.AddMember("screenColor", colorVal, allocator);
}   

void LoadScreenColor(rapidjson::Value& colorVal)
{
    config.screenColor.r = colorVal["r"].GetFloat();
    config.screenColor.g = colorVal["g"].GetFloat();
    config.screenColor.b = colorVal["b"].GetFloat();
    config.screenColor.a = 1.0f;
}

void SaveConfig()
{
    getLogger().info("Saving Configuration...");
    getConfig().config.RemoveAllMembers();
    getConfig().config.SetObject();
    rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator();
    SaveScreenColor(allocator, getConfig().config);    
    getConfig().Write();
    getLogger().info("Saved Configuration!");
}

bool LoadConfig()
{
    getLogger().info("Loading Config...");
    bool foundEverything = true;
    rapidjson::Document& doc = getConfig().config;
    
    if(doc.HasMember("screenColor")){
        LoadScreenColor(doc["screenColor"]);
    }else{
        foundEverything = false;
    } 

    if (foundEverything) getLogger().info("Config Loaded Successfully!");
    return foundEverything;
}