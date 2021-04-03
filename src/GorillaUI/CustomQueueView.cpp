#include "GorillaUI/CustomQueueView.hpp"
#include "CustomQueues.hpp"
#include "GorillaUI/BaseGameInterface.hpp"
#include "Helpers/SelectionHelper.hpp"
#include "ViewLib/CustomComputer.hpp"

DEFINE_CLASS(GorillaUI::CustomQueueView);


namespace GorillaUI
{
    void CustomQueueView::Awake()
    {
        selectionHandler = new UISelectionHandler(EKeyboardKey::Left, EKeyboardKey::Right, EKeyboardKey::Enter, true, true);
        ((UISelectionHandler*)selectionHandler)->max = CustomQueues::get_queues().size();
    }

    void CustomQueueView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&CustomQueueView::JoinQueue, this, std::placeholders::_1);
        ((UISelectionHandler*)selectionHandler)->selectionCallback = fun;
        Redraw();
    }

    void CustomQueueView::JoinQueue(int index)
    {
        const QueueInfo& info = CustomQueues::get_queue(index);
        BaseGameInterface::SetQueue(info.internal);
    }

    void CustomQueueView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawQueues();

        CustomComputer::Redraw();
    }
    
    void CustomQueueView::DrawHeader()
    {
        text += "<color=#ffff00>== <color=#fdfdfd>Custom Queues</color> ==</color>\n";
    }
    
    void CustomQueueView::DrawQueues()
    {
        text += "  <size=40>Select A Custom Queue in this screen, use <color=#fdfdfd>[<]</color> and <color=#fdfdfd>[>]</color> to navigate</size>\n";

        const QueueInfo& info = CustomQueues::get_queue(((UISelectionHandler*)selectionHandler)->currentSelectionIndex);

        text += string_format("  Currently Selected Queue: <color=#fdfdfd>%s</color>\n\n  <color=#fdfdfd>%s</color>", BaseGameInterface::Queue::get_Queue().c_str() , info.display.c_str());

        if (info.description != "")
        {
            text += string_format("\n  Description:\n%s", info.description.c_str());
        }
    }
    
    void CustomQueueView::OnKeyPressed(int key)
    {
        ((UISelectionHandler*)selectionHandler)->HandleKey((EKeyboardKey)key);
        Redraw();
    }
}