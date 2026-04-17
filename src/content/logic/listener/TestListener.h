//
// Created by Earth_Studio on 2026/4/17.
//

#ifndef CMATERIAL_TESTLISTENER_H
#define CMATERIAL_TESTLISTENER_H


#include "content/logic/event/TestEvent.hpp"
#include "engine/eventbus/IListener.h"


namespace cmaterial::event {
    class TestListener : public IListener{
    public:
        EVENTHANDLER(TestEvent, testListener)
        void testListener(TestEvent* event);
    };
}



#endif //CMATERIAL_TESTLISTENER_H
