#include "ModEntry.hpp"
#include "GorillaUI.hpp"

namespace GorillaUI
{
    ModEntry::ModEntry(ModInfo info, Il2CppClass* klass, EntryType type) : info(info), klass(klass), type(type) 
    { 
        view = nullptr; 
        viewManager = nullptr;
    }

    ModEntry::ModEntry(ModInfo info, EntryCallback callback) : info(info), callback(callback), type(EntryType::Callback) 
    { 
        view = nullptr; 
        viewManager = nullptr;
    }

    const ModInfo& ModEntry::get_info() const
    {
        return info;
    }

    Il2CppClass* ModEntry::get_class() const
    {
        return klass;
    }
    
    Components::View* ModEntry::get_view()
    {
        if (type != EntryType::View) return nullptr;
        if (!view) view = CreateView(klass);
        return view;
    }

    Components::ViewManager* ModEntry::get_viewManager()
    {
        if (type != EntryType::ViewManager) return nullptr;
        if (!viewManager) viewManager = CreateViewManager(klass);
        return viewManager;
    }

    ModEntry::EntryType ModEntry::get_type()
    {
        return type;
    }

    void ModEntry::RunCallback()
    {
        if (type != EntryType::Callback) return;
        callback();
    }
}