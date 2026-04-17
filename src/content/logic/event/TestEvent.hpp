//
// Created by Earth_Studio on 2026/4/17.
//

#ifndef CMATERIAL_TESTEVENT_H
#define CMATERIAL_TESTEVENT_H


#include "engine/eventbus/IEvent.h"

#include <string>


namespace cmaterial::event {
    class TestEvent : public IEvent {
    public:
        REGISTEREVENT(TestEvent)

        TestEvent(std::string str) { test = str; }

    protected:
        std::string test;
    };
}



#endif //CMATERIAL_TESTEVENT_H
