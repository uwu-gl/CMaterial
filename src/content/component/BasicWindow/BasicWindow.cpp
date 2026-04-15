//
// Created by Earth_Studio on 2026/4/15.
//

#include "BasicWindow.h"

#include "imgui.h"

void cmaterial::component::BasicWindow::render(ImGuiIO *io, bool &is_open, ImGuiWindowFlags flags) {
    if (ImGui::Begin("CMaterial Engine", &is_open, flags)) {
        ImGui::Text("Hello, Engine!");
        ImGui::Text("Frame time: %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);

        ImGui::Separator();

        if (ImGui::Button("Exit")) {
            is_open = false;
        }
    }
    ImGui::End();
}