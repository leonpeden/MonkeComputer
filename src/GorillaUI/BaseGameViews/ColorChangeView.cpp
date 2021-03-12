#include "GorillaUI/BaseGameViews/ColorChangeView.hpp"
#include "GorillaUI.hpp"
#include "Register.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "GorillaUI/BaseGameInterface.hpp"

DEFINE_CLASS(GorillaUI::ColorChangeView);

extern Logger& getLogger();

namespace GorillaUI
{
    void ColorChangeView::Awake()
    {
        if (!selectionHandler) selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        selectionHandler->max = 2;

        Color col = BaseGameInterface::PlayerColor::get_color();
        float* start = &col.r;
        for (int i = 0; i < 3; i++)
        {
            numberInputHandlers[i] = new UINumberInputHandler(EKeyboardKey::Enter, false);
            numberInputHandlers[i]->number = (int)(start[i] * 255);
        }
    }

    void ColorChangeView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&ColorChangeView::UpdateColor, this, std::placeholders::_1);
        selectionHandler->selectionCallback = fun;
        
        if (firstActivation)
        {
            Redraw();
        }
    }

    void ColorChangeView::UpdateColor(int num)
    {
        float r = (float)numberInputHandlers[0]->number / 255.0f;
        float g = (float)numberInputHandlers[1]->number / 255.0f;
        float b = (float)numberInputHandlers[2]->number / 255.0f;
        BaseGameInterface::SetColor(r, g, b);
    }

    void ColorChangeView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawColors();

        CustomComputer::Redraw();
    }
    
    void ColorChangeView::DrawHeader()
    {
        text += "<color=#ffff00>== <color=#fdfdfd>Color Config</color> ==</color>\n";
    }
    
    void ColorChangeView::DrawColors()
    {
        for (int i = 0; i < 3; i++)
        {
            text += "\n";
            text += selectionHandler->currentSelectionIndex == i ? "<color=#ed6540>></color> " : "  ";
            switch(i)
            {
                case 0:
                    text += string_format("Red:   %d", numberInputHandlers[i]->number);
                    break;
                case 1:
                    text += string_format("Green: %d", numberInputHandlers[i]->number);
                    break;
                case 2:
                    text += string_format("Blue:  %d", numberInputHandlers[i]->number);
                    break;
                default:
                    break;
            }
            text += "\n";
        }
    }
    
    void ColorChangeView::OnKeyPressed(int key)
    {
        selectionHandler->HandleKeyPress((EKeyboardKey)key);
        UINumberInputHandler* currentNumberHandler = numberInputHandlers[selectionHandler->currentSelectionIndex];
        currentNumberHandler->HandleKey((EKeyboardKey)key);
        if (currentNumberHandler->number > 255) currentNumberHandler->number = 255;
        Redraw();
    }
}