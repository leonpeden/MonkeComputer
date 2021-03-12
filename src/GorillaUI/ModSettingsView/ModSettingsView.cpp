#include "GorillaUI/ModSettingsView/ModSettingsView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/CustomComputer.hpp"

DEFINE_CLASS(GorillaUI::ModSettingsView);

extern Logger& getLogger();

namespace GorillaUI
{
    void ModSettingsView::Awake()
    {
        if (!selectionHandler) selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        selectionHandler->max = Register::get_entries().size();
    }

    void ModSettingsView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&ModSettingsView::ShowModView, this, std::placeholders::_1);
        selectionHandler->selectionCallback = fun;
        
        if (firstActivation)
        {
            getLogger().info("ModSettings View First activation!");
            Redraw();
        }
    }

    void ModSettingsView::ShowModView(int index)
    {
        std::vector<ModEntry>& entries = Register::get_entries();
        if (entries.size() == 0) return;
        ModEntry& entry = entries[selectionHandler->currentSelectionIndex];
        switch(entry.get_type())
        {
            case ModEntry::EntryType::View:
                CustomComputer::instance->activeViewManager->ReplaceTopView(entry.get_view());
                break;
            case ModEntry::EntryType::ViewManager:
                CustomComputer::instance->activeViewManager->PresentViewManager(entry.get_viewManager());
                break;
            default:
                return;
        }
    }

    void ModSettingsView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawMods();

        CustomComputer::Redraw();
    }
    
    void ModSettingsView::DrawHeader()
    {
        text += "<color=#ffff00>== <color=#fdfdfd>Mod Settings</color> ==</color>\n";
    }
    
    void ModSettingsView::DrawMods()
    {
        const std::vector<ModEntry>& entries = Register::get_entries();
        int i = 0;
        for (auto& e : entries)
        {
            text += selectionHandler->currentSelectionIndex == i ? "<color=#ed6540>></color> " : "  ";
            text += e.get_info().id;
            text += "\n";
            i++;
        }
    }
    
    void ModSettingsView::OnKeyPressed(int key)
    {
        selectionHandler->HandleKey((EKeyboardKey)key);
        Redraw();
    }
}