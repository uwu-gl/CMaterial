//
// Created by Earth_Studio on 2026/4/16.
//

#include "IListener.h"

#include "EventBus.h"

namespace cmaterial::event {
    IListener::~IListener() {
        //EventBus::subscriberMap.erase(listenEventName);
    }
}