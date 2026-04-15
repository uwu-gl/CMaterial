//
// Created by Earth_Studio on 2026/4/15.
//

#ifndef CMATERIAL_FRAMEWORK_H
#define CMATERIAL_FRAMEWORK_H

#include "imgui.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace cmaterial {
    class Framework {
        enum error {
            OK,
            NOT_INIT,
            GLFW_INIT_FAILED,
            GLFW_CREATE_WINDOW_FAILED,
            GLAD_LOAD_GL_FAILED
        };

    public:
        Framework();

        error initialize();
        error run();

        ~Framework();

    private:
        bool initialized;

        ImGuiIO *io;
        GLFWwindow *hidden_window;
        bool is_open;
    };
}



#endif //CMATERIAL_FRAMEWORK_H
