#include "GorillaUI/BaseGameViews/QueueChangeView.hpp"
#include "ViewLib/CustomComputer.hpp"
#include "Helpers/SelectionHelper.hpp"
#include "GorillaUI/BaseGameInterface.hpp"

DEFINE_CLASS(GorillaUI::QueueChangeView);

extern Logger& getLogger();

namespace GorillaUI
{
    void QueueChangeView::Awake()
    {
        if (!selectionHandler) selectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true);
        selectionHandler->max = 2;

        std::string queueType = BaseGameInterface::Queue::get_Queue();
        selectionHandler->currentSelectionIndex = BaseGameInterface::Queue::queueToIndex(queueType);
    }

    void QueueChangeView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&QueueChangeView::ChangeQueue, this, std::placeholders::_1);
        selectionHandler->selectionCallback = fun;
        Redraw();
    }

    void QueueChangeView::ChangeQueue(int index)
    {
        std::string type = "";
        switch(index)
        {
            case 0:
                type = "DEFAULT";
                break;
            case 1:
                type = "COMPETITIVE";
                break;
            default:
                break;
        }

        BaseGameInterface::SetQueue(type);
    }

    void QueueChangeView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawQueues();

        CustomComputer::Redraw();
    }
    
    void QueueChangeView::DrawHeader()
    {
        text += "<color=#ffff00>== <color=#fdfdfd>Settings/Queue</color> ==</color>\n";
    }
    
    void QueueChangeView::DrawQueues()
    {
        text += string_format(" <size=40>Change The Queue settings in this menu\n  Press enter to confirm your choice\n</size> Current Queue: <color=#fdfdfd>%s</color>\n", BaseGameInterface::Queue::get_Queue().c_str());

        std::vector<std::string> queues = {
            "Default",
            "Competitive"
        };
        
        SelectionHelper::DrawSelection(queues, selectionHandler->currentSelectionIndex, text);

        text += "\n<size=40> This option affects who you play with.\n";
        switch (selectionHandler->currentSelectionIndex)
        {
            case 0:
                text += " Default: Most players will choose this queue,\n expect new players all the way up to pros\n";
                break;
            case 1:
                text += " Competetive: For players looking for a challenge,\n expect pros and people looking to improve their monke skills\n";
                break;
            default:
                break;
        }

        text += "</size>";

    }
    
    void QueueChangeView::OnKeyPressed(int key)
    {
        selectionHandler->HandleKey((EKeyboardKey)key);
        Redraw();
    }
}