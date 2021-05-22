#include "GorillaUI/ModSettingsView/ModSettingsView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "Helpers/PageHelper.hpp"
#include "Helpers/SelectionHelper.hpp"

DEFINE_TYPE(GorillaUI::ModSettingsView);

extern Logger& getLogger();

#define SETTINGS_PAGE_SIZE 8
namespace GorillaUI
{
    void ModSettingsView::Awake()
    {
        if (!selectionHandler) selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        if (!pageSelectionHandler) pageSelectionHandler = new UISelectionHandler(EKeyboardKey::Left, EKeyboardKey::Right, EKeyboardKey::Enter, false, true);

        selectionHandler->max = SETTINGS_PAGE_SIZE;
        std::vector<ModEntry>& mods = Register::get_settingsEntries();
        modCount = mods.size();
        pageCount = PageHelper::GetPageAmount(mods, SETTINGS_PAGE_SIZE);
        pageSelectionHandler->max = pageCount;

        if (modCount < SETTINGS_PAGE_SIZE)
        {
            selectionHandler->max = modCount;
        }
    }

    void ModSettingsView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&ModSettingsView::ShowModView, this, std::placeholders::_1);
        selectionHandler->selectionCallback = fun;
        Redraw();
    }

    void ModSettingsView::ShowModView(int index)
    {
        index += (SETTINGS_PAGE_SIZE * pageSelectionHandler->currentSelectionIndex);
        if (modCount == 0) return;

        ModEntry& entry = Register::get_settingsEntry(index);
        switch(entry.get_type())
        {
            case ModEntry::EntryType::View:
                computer->activeViewManager->ReplaceTopView(entry.get_view());
                break;
            case ModEntry::EntryType::ViewManager:
                computer->activeViewManager->PresentViewManager(entry.get_viewManager());
                break;
            case ModEntry::EntryType::Callback:
                entry.RunCallback();
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
        std::vector<ModEntry> entries = PageHelper::GetPage(Register::get_settingsEntries(), SETTINGS_PAGE_SIZE, pageSelectionHandler->currentSelectionIndex);
        selectionHandler->max = entries.size();
        selectionHandler->currentSelectionIndex = selectionHandler->currentSelectionIndex >= entries.size() ? entries.size() - 1 : selectionHandler->currentSelectionIndex;
        std::vector<std::string> modNames = {};
        
        for (auto e : entries)
        {
            modNames.push_back(e.get_info().id);
        }

        SelectionHelper::DrawSelection(modNames, selectionHandler->currentSelectionIndex, text);
    }
    
    void ModSettingsView::OnKeyPressed(int key)
    {
        if (modCount == 0) return;
        selectionHandler->HandleKey((EKeyboardKey)key);
        pageSelectionHandler->HandleKey((EKeyboardKey)key);
        
        Redraw();
    }
}