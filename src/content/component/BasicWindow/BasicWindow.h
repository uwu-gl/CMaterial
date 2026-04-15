//
// Created by Earth_Studio on 2026/4/15.
//

#ifndef CMATERIAL_BASICWINDOW_H
#define CMATERIAL_BASICWINDOW_H

#include "engine/component/IComponent.h"
#include "imgui.h"

namespace cmaterial::component{
    class BasicWindow : public IComponent {
    public:
        BasicWindow() = default;
        ~BasicWindow() = default;

        void render(ImGuiIO *io) override;

    private:
        bool is_open = true;
    };
}



#endif //CMATERIAL_BASICWINDOW_H
