//
// Created by Earth_Studio on 2026/4/15.
//

#ifndef CMATERIAL_ICOMPONENT_H
#define CMATERIAL_ICOMPONENT_H
#include "imgui.h"


namespace cmaterial::component {
    class IComponent {
    public:
        virtual ~IComponent() = default;
        virtual void render(ImGuiIO *io, bool &is_open, ImGuiWindowFlags flags) = 0;
    };
}



#endif //CMATERIAL_ICOMPONENT_H
