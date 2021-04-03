#pragma once

#include <string>
#include <map>
#include <vector>

namespace GorillaUI
{
    struct QueueInfo {
        std::string internal = "DEFAULT";
        std::string display = "Default";
        std::string description= "";

        QueueInfo() {};
        QueueInfo(std::string internal, std::string display, std::string description) : internal(internal), display(display), description(description) {};
    };
    
    typedef std::map<std::string, QueueInfo> CustomQueueList;
    
    class CustomQueues
    {
        public:
            static void add_queue(std::string internal);
            static void add_queue(std::string internal, std::string display);
            static void add_queue(std::string internal, std::string display, std::string description);
            static void remove_queue(std::string internal);
            static void remove_queue(int queue);

            static const CustomQueueList& get_queues();
            static const QueueInfo& get_queue(int queue);
            static const QueueInfo& get_queue(std::string internal);

        private:
            static inline CustomQueueList queues = {};
    };
}