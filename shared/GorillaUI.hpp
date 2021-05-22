#pragma once
#include "../shared/ViewLib/ViewManager.hpp"
#include "../shared/ViewLib/View.hpp"

namespace GorillaUI
{
    void Init();
    void Innit();
    Components::ViewManager* CreateViewManager(Il2CppClass* klass);
    Components::View* CreateView(Il2CppClass* klass);

    template<class T = Components::View*>
    T CreateView()
    {
        static_assert(std::is_convertible<T, Components::View*>());
        return reinterpret_cast<T>(CreateView(classof(T)));
    }

    template<class T = Components::ViewManager*>
    T CreateViewManager()
    {
        static_assert(std::is_convertible<T, Components::ViewManager*>());
        return reinterpret_cast<T>(CreateViewManager(classof(T)));
    }
}   