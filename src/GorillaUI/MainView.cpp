#include "GorillaUI/MainView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "Helpers/SelectionHelper.hpp"
#include "Helpers/PageHelper.hpp"
DEFINE_TYPE(GorillaUI::MainView);

extern Logger& getLogger();

#define MENU_PAGE_SIZE 5

namespace GorillaUI
{
    void MainView::Awake()
    {
        if (!selectionHandler) selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        if (!pageSelectionHandler) pageSelectionHandler = new UISelectionHandler(EKeyboardKey::Left, EKeyboardKey::Right, EKeyboardKey::Enter, false, true);

        selectionHandler->max = MENU_PAGE_SIZE;
        std::vector<ModEntry>& mods = Register::get_entries();
        entryCount = mods.size();
        pageCount = PageHelper::GetPageAmount(mods, MENU_PAGE_SIZE);
        pageSelectionHandler->max = pageCount;

        if (entryCount < MENU_PAGE_SIZE)
        {
            selectionHandler->max = entryCount;
        }

        screenSaver = true;
    }

    void MainView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&MainView::ShowView, this, std::placeholders::_1);
        selectionHandler->selectionCallback = fun;
        
        if (!firstActivation)
            Redraw();
    }

    void MainView::ShowView(int index)
    {
        index += (MENU_PAGE_SIZE * pageSelectionHandler->currentSelectionIndex);
        if (entryCount == 0) return;

        ModEntry& entry = Register::get_entry(index);
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

    void MainView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawSubMenus();

        if (pageCount > 1)
        {
            text += "\n";
            text += string_format("  Page %d/%d", pageSelectionHandler->currentSelectionIndex, pageCount - 1);
        }

        computer->Redraw();
    }
    
    void MainView::DrawHeader()
    {
        text += "<color=#ffff00>===========================================</color>\n";
        text += "               <color=#00ff00>MonkeComputer</color>\n";
        text += "              by: <color=#ff0000>RedBrumbler</color>\n";
        text += "<color=#ffff00>===========================================</color>\n";
    }
    
    void MainView::DrawSubMenus()
    {
        std::vector<ModEntry> entries = PageHelper::GetPage(Register::get_entries(), MENU_PAGE_SIZE, pageSelectionHandler->currentSelectionIndex);
        selectionHandler->max = entries.size();
        selectionHandler->currentSelectionIndex = selectionHandler->currentSelectionIndex >= entries.size() ? entries.size() - 1 : selectionHandler->currentSelectionIndex;
        std::vector<std::string> menuNames = {};
        
        for (auto e : entries)
        {
            menuNames.push_back(e.get_info().id);
        }

        SelectionHelper::DrawSelection(menuNames, selectionHandler->currentSelectionIndex, text);

        for (int i = entries.size(); i <= MENU_PAGE_SIZE; i++)
        {
            text +="\n"; 
        }
    }
    
    void MainView::OnKeyPressed(int key)
    {
        if (entryCount == 0) return;
        if (!screenSaver)
        {
            selectionHandler->HandleKey((EKeyboardKey)key);
            pageSelectionHandler->HandleKey((EKeyboardKey)key);
        }
        else screenSaver = false;
        Redraw();
    }
}