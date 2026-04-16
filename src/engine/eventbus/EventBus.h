//
// Created by Earth_Studio on 2026/4/16.
//

#ifndef CMATERIAL_EVENTBUS_H
#define CMATERIAL_EVENTBUS_H


#include <string>
#include <unordered_map>


namespace cmaterial::event {
    class EventBus {
    public:
        EventBus() = default;
        ~EventBus();

    //private:
        static std::unordered_map<std::string, std::vector<int>> subscriberMap;
    };
}



#endif //CMATERIAL_EVENTBUS_H
