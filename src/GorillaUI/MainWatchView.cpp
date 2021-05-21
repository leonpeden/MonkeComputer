#include "GorillaUI/MainWatchView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/MonkeWatch.hpp"

#include "Helpers/SelectionHelper.hpp"
#include "Helpers/PageHelper.hpp"
DEFINE_TYPE(GorillaUI::MainWatchView);

extern Logger& getLogger();

#define MENU_PAGE_SIZE 12

namespace GorillaUI
{
    void MainWatchView::Awake()
    {
        if (!selectionHandler) selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        if (!pageSelectionHandler) pageSelectionHandler = new UISelectionHandler(EKeyboardKey::Left, EKeyboardKey::Right, EKeyboardKey::Enter, false, true);

        selectionHandler->max = MENU_PAGE_SIZE;
        std::vector<ModEntry>& mods = Register::get_watchEntries();
        entryCount = mods.size();
        pageCount = PageHelper::GetPageAmount(mods, MENU_PAGE_SIZE);
        pageSelectionHandler->max = pageCount;

        if (entryCount < MENU_PAGE_SIZE)
        {
            selectionHandler->max = entryCount;
        }

        screenSaver = true;
    }

    void MainWatchView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&MainWatchView::ShowView, this, std::placeholders::_1);
        selectionHandler->selectionCallback = fun;
        
        if (!firstActivation)
            Redraw();
    }

    void MainWatchView::ShowView(int index)
    {
        index += (MENU_PAGE_SIZE * pageSelectionHandler->currentSelectionIndex);
        if (entryCount == 0) return;

        ModEntry& entry = Register::get_watchEntry(index);
        switch(entry.get_type())
        {
            case ModEntry::EntryType::View:
                MonkeWatch::get_instance()->activeViewManager->ReplaceTopView(entry.get_view());
                break;
            case ModEntry::EntryType::ViewManager:
                MonkeWatch::get_instance()->activeViewManager->PresentViewManager(entry.get_viewManager());
                break;
            default:
                return;
        }
    }

    void MainWatchView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawSubMenus();

        if (pageCount > 1)
        {
            text += "\n";
            text += string_format("  Page %d/%d", pageSelectionHandler->currentSelectionIndex, pageCount - 1);
        }

        MonkeWatch::get_instance()->Redraw();
    }
    
    void MainWatchView::DrawHeader()
    {
        text += "<color=#ffff00>========================</color>\n";
        text += "       <color=#00ff00>MonkeWatch</color>\n";
        text += "     <color=#fdfdfd>by:</color> <color=#ff0000>RedBrumbler</color>\n";
        text += "<color=#ffff00>========================</color>\n";
    }
    
    void MainWatchView::DrawSubMenus()
    {
        std::vector<ModEntry> entries = PageHelper::GetPage(Register::get_watchEntries(), MENU_PAGE_SIZE, pageSelectionHandler->currentSelectionIndex);
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
    
    void MainWatchView::OnKeyPressed(int key)
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