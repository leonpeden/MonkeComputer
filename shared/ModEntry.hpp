#pragma once
#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "ViewLib/View.hpp"

namespace GorillaUI
{
    class ModEntry
    {
        public:
            ModEntry(ModInfo info, Il2CppClass* entryView);
            const ModInfo& get_info() const;
            Il2CppClass* get_viewClass() const;
            Components::View* get_view();
            
        private:
            ModInfo info;
            Il2CppClass* entryView;
            Components::View* view;
    };
}