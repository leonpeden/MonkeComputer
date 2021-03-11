#include "ModEntry.hpp"
#include "GorillaUI.hpp"

namespace GorillaUI
{
    ModEntry::ModEntry(ModInfo info, Il2CppClass* entryView) : info(info), entryView(entryView) { view = nullptr; };

    const ModInfo& ModEntry::get_info() const
    {
        return info;
    }

    Il2CppClass* ModEntry::get_viewClass() const
    {
        return entryView;
    }
    
    Components::View* ModEntry::get_view()
    {
        if (!view) view = CreateView(entryView);
        return view;
    }
}