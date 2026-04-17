//
// Created by Earth_Studio on 2026/4/16.
//

#ifndef CMATERIAL_EVENTBUS_H
#define CMATERIAL_EVENTBUS_H


#include <vector>
#include <unordered_map>
#include <mutex>

#include "IListener.h"


namespace cmaterial::event {
    class IListener;
    class IHandler;
    class IEvent;

    class EventBus {
    public:
        EventBus() = default;
        ~EventBus();

        void subscribe(IListener* listener);
        void post(IEvent* event);
        void dispatch();

    private:
        std::vector<IListener*> registeredListeners;
        std::unordered_map<const void*, std::vector<IHandler*>> subscriberMap;

        std::vector<IEvent*> eventQueue ;
        std::mutex queueMutex;
    };
}




#endif //CMATERIAL_EVENTBUS_H
