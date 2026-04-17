//
// Created by Earth_Studio on 2026/4/16.
//

#include "IListener.h"

#include "EventBus.h"

namespace cmaterial::event {
    const std::vector<IHandler *> &IListener::getHandlers() const {
        return handlers;
    }

    void IListener::_add_handler(IHandler *h) {
        handlers.push_back(h);
    }

    IListener::~IListener() {
        for (auto* h : handlers) delete h;
    }
}
