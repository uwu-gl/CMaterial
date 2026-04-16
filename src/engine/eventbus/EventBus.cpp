//
// Created by Earth_Studio on 2026/4/16.
//

#include "EventBus.h"

namespace cmaterial::event {
    void test1() {
    }

    void test2() {
        //EventBus::test.push_back(&test1);
    }

    EventBus::~EventBus() {
        //test.clear();
    }
}