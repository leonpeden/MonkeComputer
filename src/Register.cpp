#include "Register.hpp"

namespace GorillaUI
{
    void Register::RegisterView(ModInfo info, Il2CppClass* klass)
    {
        entries.push_back(ModEntry(info, klass, ModEntry::EntryType::View));
    }

    void Register::RegisterView(std::string name, std::string version, Il2CppClass* klass)
    {
        entries.push_back(ModEntry({name, version}, klass, ModEntry::EntryType::View));
    }

    void Register::RegisterViewManager(ModInfo info, Il2CppClass* klass)
    {
        entries.push_back(ModEntry(info, klass, ModEntry::EntryType::ViewManager));
    }

    void Register::RegisterViewManager(std::string name, std::string version, Il2CppClass* klass)
    {
        entries.push_back(ModEntry({name, version}, klass, ModEntry::EntryType::ViewManager));
    }

    void Register::RegisterSettingsView(ModInfo info, Il2CppClass* klass)
    {
        settingsentries.push_back(ModEntry(info, klass, ModEntry::EntryType::View));
    }

    void Register::RegisterSettingsView(std::string name, std::string version, Il2CppClass* klass)
    {
        settingsentries.push_back(ModEntry({name, version}, klass, ModEntry::EntryType::View));
    }

    void Register::RegisterSettingsViewManager(ModInfo info, Il2CppClass* klass)
    {
        settingsentries.push_back(ModEntry(info, klass, ModEntry::EntryType::ViewManager));
    }

    void Register::RegisterSettingsViewManager(std::string name, std::string version, Il2CppClass* klass)
    {
        settingsentries.push_back(ModEntry({name, version}, klass, ModEntry::EntryType::ViewManager));
    }

    void Register::RegisterWatchView(ModInfo info, Il2CppClass* klass)
    {
        watchentries.push_back(ModEntry(info, klass, ModEntry::EntryType::View));
    }

    void Register::RegisterWatchView(std::string name, std::string version, Il2CppClass* klass)
    {
        watchentries.push_back(ModEntry({name, version}, klass, ModEntry::EntryType::View));
    }

    void Register::RegisterWatchViewManager(ModInfo info, Il2CppClass* klass)
    {
        watchentries.push_back(ModEntry(info, klass, ModEntry::EntryType::ViewManager));
    }

    void Register::RegisterWatchViewManager(std::string name, std::string version, Il2CppClass* klass)
    {
        watchentries.push_back(ModEntry({name, version}, klass, ModEntry::EntryType::ViewManager));
    }

    std::vector<ModEntry>& Register::get_entries()
    {
        return entries;
    }

    std::vector<ModEntry>& Register::get_settingsEntries()
    {
        return settingsentries;
    }

    std::vector<ModEntry>& Register::get_watchEntries()
    {
        return watchentries;
    }

    ModEntry& Register::get_entry(int index)
    {
        return entries[index];
    }

    ModEntry& Register::get_settingsEntry(int index)
    {
        return settingsentries[index];
    }

    ModEntry& Register::get_watchEntry(int index)
    {
        return watchentries[index];
    }
}