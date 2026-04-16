//
// Created by Earth_Studio on 2026/4/16.
//

#ifndef CMATERIAL_ILISTENER_H
#define CMATERIAL_ILISTENER_H


#include <string>


namespace cmaterial::event {
    class IListener {
        enum Order {
            FIRST,
            DEFAULT,
            LAST,
        };

    public:
        virtual ~IListener();

        std::string listenEventName;
        Order order = DEFAULT;
    };
}


#endif // CMATERIAL_ILISTENER_H
