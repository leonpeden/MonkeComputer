#pragma once
#include "../shared/ModEntry.hpp"
#include <vector>
#include <type_traits>

namespace GorillaUI
{
    class Register
    {
        public:
            template<class T>
            static void RegisterView(std::string name, std::string version) 
            {
                static_assert(std::is_convertible<T, Components::View*>());
                RegisterView({name, version}, classof(T));
            }

            template<class T>
            static void RegisterView(ModInfo info) 
            {
                static_assert(std::is_convertible<T, Components::View*>());
                RegisterView(info, classof(T));
            }

            template<class T>
            static void RegisterViewManager(std::string name, std::string version) 
            {
                static_assert(std::is_convertible<T, Components::ViewManager*>());
                RegisterViewManager({name, version}, classof(T));
            }

            template<class T>
            static void RegisterViewManager(ModInfo info) 
            {
                static_assert(std::is_convertible<T, Components::ViewManager*>());
                RegisterViewManager(info, classof(T));
            }

            static std::vector<ModEntry>& get_entries();
            
        private:
            static inline std::vector<ModEntry> entries = {};
            static void RegisterView(ModInfo info, Il2CppClass* klass);
            static void RegisterView(std::string name, std::string version, Il2CppClass* klass);
            static void RegisterViewManager(ModInfo info, Il2CppClass* klass);
            static void RegisterViewManager(std::string name, std::string version, Il2CppClass* klass);
    };
}