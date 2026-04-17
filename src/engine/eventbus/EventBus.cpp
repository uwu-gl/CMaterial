//
// Created by Earth_Studio on 2026/4/16.
//

#include "EventBus.h"
#include <algorithm>
#include "IEvent.h"
#include "IListener.h"

namespace cmaterial::event {

    void EventBus::subscribe(IListener* listener) {
        if (!listener) return;

        registeredListeners.push_back(listener);

        for (auto* handler : listener->getHandlers()) {
            auto& vec = subscriberMap[handler->getEventType()];
            vec.push_back(handler);

            std::sort(vec.begin(), vec.end(),[](IHandler* a, IHandler* b) {
                return a->getOrder() < b->getOrder();
            });
        }
    }

    void EventBus::post(IEvent* event) {
        if (!event) return;

        std::lock_guard<std::mutex> lock(queueMutex);
        eventQueue.push_back(event);
    }

    void EventBus::dispatch() {
        std::vector<IEvent*> processingQueue;
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            if (eventQueue.empty()) return;
            processingQueue.swap(eventQueue);
        }

        for (auto* event : processingQueue) {
            const void* type = event->getEventType();
            if (subscriberMap.contains(type)) {
                for (auto* handler : subscriberMap[type]) {
                    // 支持取消逻辑
                    if (event->getIsCancelled()) break;
                    handler->execute(event);
                }
            }
            delete event;
        }
    }

    EventBus::~EventBus() {
        std::lock_guard<std::mutex> lock(queueMutex);
        for (auto* e : eventQueue) delete e;
        eventQueue.clear();

        for (IListener* listener : registeredListeners) {
            delete listener;
        }
    }
}