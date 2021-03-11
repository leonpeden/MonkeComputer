#pragma once
#include "ViewLib/ViewManager.hpp"
#include "ViewLib/View.hpp"

namespace GorillaUI
{
    Components::ViewManager* CreateViewManager(Il2CppClass* klass);
    Components::View* CreateView(Il2CppClass* klass);

    template<class T = Il2CppObject*>
    T CreateView()
    {
        return reinterpret_cast<T>(CreateView(classof(T)));
    }

    template<class T = Il2CppObject*>
    T CreateViewManager()
    {
        return reinterpret_cast<T>(CreateViewManager(classof(T)));
    }
}   