//
// Created by Earth_Studio on 2026/4/15.
//

#ifndef CMATERIAL_FRAMEWORK_H
#define CMATERIAL_FRAMEWORK_H



#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "imgui.h"

#include "engine/component/IComponent.h"
#include "engine/eventbus/EventBus.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace cmaterial {
    class Framework {
    public:
        enum error {
            OK,
            NOT_INIT,
            GLFW_INIT_FAILED,
            GLFW_CREATE_WINDOW_FAILED,
            GLAD_LOAD_GL_FAILED
        };

        Framework();
        ~Framework();

        error initialize();
        error run();

        void addComponent(component::IComponent *component);
        void addListener(event::IListener *listener);

        event::EventBus* getEventBus();

    private:
        bool initialized;

        ImGuiIO *io;
        GLFWwindow *hidden_window;
        std::unordered_map<std::string, component::IComponent *> components;
        std::vector<std::string> deadComponentNames;

        event::EventBus eventBus;
    };
}



#endif //CMATERIAL_FRAMEWORK_H
