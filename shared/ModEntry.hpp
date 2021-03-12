#pragma once
#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "../shared/ViewLib/View.hpp"
#include "../shared/ViewLib/ViewManager.hpp"

namespace GorillaUI
{
    class ModEntry
    {
        public:
            enum class EntryType{
                View,
                ViewManager
            };
            ModEntry(ModInfo info, Il2CppClass* klass, EntryType type);
            const ModInfo& get_info() const;
            Il2CppClass* get_class() const;
            Components::View* get_view();
            Components::ViewManager* get_viewManager();
            EntryType get_type();
        private:
            EntryType type;
            ModInfo info;
            Il2CppClass* klass;
            Components::View* view;
            Components::ViewManager* viewManager;
    };
}