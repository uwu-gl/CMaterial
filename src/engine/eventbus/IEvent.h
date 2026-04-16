//
// Created by Earth_Studio on 2026/4/16.
//

#ifndef CMATERIAL_IEVENT_H
#define CMATERIAL_IEVENT_H



namespace cmaterial::event {
    class IEvent {
    public:
        virtual ~IEvent() = default;

        typedef const void* EventID;
    };
}




#endif //CMATERIAL_IEVENT_H
