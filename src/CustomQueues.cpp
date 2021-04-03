#include "CustomQueues.hpp"

static GorillaUI::QueueInfo defaultInfo = {"DEFAULT", "Default", ""};

namespace GorillaUI
{
    void CustomQueues::add_queue(std::string internal)
    {
        std::string display = "";
        bool first = true;

        for (auto c : internal)
        {
            if (first)
            {
                first = false;
                display += c;
            }
            else 
                display += tolower(c);
        }

        add_queue(internal, display);
    }

    void CustomQueues::add_queue(std::string internal, std::string display)
    {
        add_queue(internal, display, "");
    }

    void CustomQueues::add_queue(std::string internal, std::string display, std::string description)
    {
        QueueInfo info = {internal, display, description};
        queues[internal] = info;
    }

    void CustomQueues::remove_queue(std::string internal)
    {
        CustomQueueList::iterator it = queues.find(internal);

        if (it != queues.end()) 
        {
            queues.erase(it);
        }
    }

    void CustomQueues::remove_queue(int index)
    {
        int i = 0;
        for (auto& q : queues)
        {
            if (i == index) 
            {
                remove_queue(q.second.internal);
                return;
            }
            i++;
        }
    }

    const QueueInfo& CustomQueues::get_queue(std::string internal)
    {
        CustomQueueList::iterator it = queues.find(internal);

        if (it != queues.end())
        {
            return it->second;
        }

        return defaultInfo;
    }

    const QueueInfo& CustomQueues::get_queue(int index)
    {
        int i = 0;
        for (auto& q : queues)
        {
            if (i == index) return q.second;
            i++;
        }

        return defaultInfo;
    }

    const CustomQueueList& CustomQueues::get_queues()
    {
        return queues;
    }
}