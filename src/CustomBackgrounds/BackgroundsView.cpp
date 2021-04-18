#include "CustomBackgrounds/BackgroundsView.hpp"
#include "GorillaUI/BaseGameInterface.hpp"
#include "Helpers/SelectionHelper.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "CustomBackgrounds/BackgroundsList.hpp"
#include "Utils/LoadUtils.hpp"
#include "Helpers/PageHelper.hpp"
#include "Helpers/SelectionHelper.hpp"
#include "quest-cosmetic-loader/shared/FileUtils.hpp"
#include "config.hpp"
DEFINE_TYPE(GorillaUI::BackgroundsView);

#include "UnityEngine/Texture2D.hpp"

#define BACKGROUND_PAGE_SIZE 10

using namespace UnityEngine;

namespace GorillaUI
{
    void BackgroundsView::Awake()
    {
        selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true, true);
        pageSelectionHandler = new UISelectionHandler(EKeyboardKey::Left, EKeyboardKey::Right, EKeyboardKey::Enter, false, true);

        selectionHandler->max = BACKGROUND_PAGE_SIZE;
        bgCount = BackgroundsList::get_list().size();
        pageCount = PageHelper::GetPageAmount(BackgroundsList::get_list(), BACKGROUND_PAGE_SIZE);
        pageSelectionHandler->max = pageCount;

        if (bgCount < BACKGROUND_PAGE_SIZE)
        {
            selectionHandler->max = bgCount;
        }
    }

    void BackgroundsView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&BackgroundsView::LoadTexture, this, std::placeholders::_1);
        selectionHandler->selectionCallback = fun;
        Redraw();
    }

    void BackgroundsView::LoadTexture(int index)
    {
        if (bgCount == 0) return;
        index += BACKGROUND_PAGE_SIZE * pageSelectionHandler->currentSelectionIndex;

        std::string filePath = "sdcard/ModData/com.AnotherAxiom.GorillaTag/Mods/MonkeComputer/Backgrounds/" + BackgroundsList::get_fileName(index);
        if (config.lastActiveBackground == filePath && config.lastActiveBackground != "")
        {
            config.lastActiveBackground = "";
            CustomComputer::get_instance()->SetBGTex(nullptr);
        }
        else
        {
            config.lastActiveBackground = filePath;
            CustomComputer::get_instance()->SetBGTex(LoadUtils::LoadTextureFromFile(filePath));
        }
        SaveConfig();
    }

    void BackgroundsView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawBackgrounds();

        CustomComputer::Redraw();
    }
    
    void BackgroundsView::DrawHeader()
    {
        text += string_format("<color=#ffff00>== <color=#fdfdfd>Custom Backgrounds</color> ==</color> page %d/%d\n", pageSelectionHandler->currentSelectionIndex + 1, pageSelectionHandler->max);
    }
    
    void BackgroundsView::DrawBackgrounds()
    {
        if (bgCount == 0)
        {
            text += "<size=40>\n";
            text += "    You have 0 backgrounds in your backgrounds folder,\n";
            text += "    Put them in the following folder to have them show:\n";
            text += "    <color=#fdfdfd>sdcard/ModData/com.AnotherAxiom.GorillaTag/Mods/MonkeComputer/Backgrounds/</color>\n";
            text += "\n</size>";
        }
        else
        {
            std::vector<std::string>& list = BackgroundsList::get_list();

            std::vector<std::string> page = PageHelper::GetPage(list, BACKGROUND_PAGE_SIZE, pageSelectionHandler->currentSelectionIndex);

            selectionHandler->max = page.size();
            selectionHandler->currentSelectionIndex = selectionHandler->currentSelectionIndex >= page.size() ? page.size() - 1 : selectionHandler->currentSelectionIndex;
            std::vector<std::string> display = {};

            for (auto f : page)
            {
                display.push_back(f.substr(0, f.find_first_of(".")));
            }

            SelectionHelper::DrawSelection(display, selectionHandler->currentSelectionIndex, text);
        }
    }
    
    void BackgroundsView::OnKeyPressed(int key)
    {
        selectionHandler->HandleKey((EKeyboardKey)key);
        pageSelectionHandler->HandleKey((EKeyboardKey)key);
        Redraw();
    }
}