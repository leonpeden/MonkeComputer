#include "MonkeComputerConfigView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "GorillaUI/BaseGameInterface.hpp"
#include "config.hpp"
#include "Helpers/SelectionHelper.hpp"
DEFINE_CLASS(GorillaUI::MonkeComputerConfigView);

extern Logger& getLogger();

namespace GorillaUI
{
    void MonkeComputerConfigView::Awake()
    {
        if (!selectionHandler) selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        selectionHandler->max = 3;

        float* start = &config.screenColor.r;
        for (int i = 0; i < 3; i++)
        {
            numberInputHandlers[i] = new UINumberInputHandler(EKeyboardKey::Enter, false);
            numberInputHandlers[i]->number = (int)(start[i] * 255);
            numberInputHandlers[i]->max = 255;
        }
    }

    void MonkeComputerConfigView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&MonkeComputerConfigView::UpdateColor, this, std::placeholders::_1);
        selectionHandler->selectionCallback = fun;
        
        if (firstActivation)
        {
            Redraw();
        }
    }

    void MonkeComputerConfigView::UpdateColor(int num)
    {
        float r = (float)numberInputHandlers[0]->number / 255.0f;
        float g = (float)numberInputHandlers[1]->number / 255.0f;
        float b = (float)numberInputHandlers[2]->number / 255.0f;
        
        CustomComputer::instance->SetBG(r, g, b);
    }

    void MonkeComputerConfigView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawColors();

        CustomComputer::Redraw();
    }
    
    void MonkeComputerConfigView::DrawHeader()
    {
        text += "<color=#ffff00>== <color=#fdfdfd>Monke Computer</color> ==</color>\n";
    }
    
    void MonkeComputerConfigView::DrawColors()
    {
        text += "\n Monitor Color:<size=40>\n  select values between 0 - 255\n</size>";
        std::vector<std::string> colors = {
            string_format("Red:   <color=#fdfdfd>%d</color>", numberInputHandlers[0]->number),
            string_format("Green: <color=#fdfdfd>%d</color>", numberInputHandlers[1]->number),
            string_format("Blue:  <color=#fdfdfd>%d</color>", numberInputHandlers[2]->number)
        };

        SelectionHelper::DrawSelection(colors, selectionHandler->currentSelectionIndex, text);
    }
    
    void MonkeComputerConfigView::OnKeyPressed(int key)
    {
        selectionHandler->HandleKey((EKeyboardKey)key);
        UINumberInputHandler* currentNumberHandler = numberInputHandlers[selectionHandler->currentSelectionIndex];
        currentNumberHandler->HandleKey((EKeyboardKey)key);
        Redraw();
    }
}