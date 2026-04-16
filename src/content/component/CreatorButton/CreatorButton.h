//
// Created by Earth_Studio on 2026/4/16.
//

#ifndef CMATERIAL_CREATORBUTTON_H
#define CMATERIAL_CREATORBUTTON_H



#include "content/component/BasicWindow/BasicWindow.h"
#include "engine/component/IComponent.h"
#include "engine/framework/Framework.h"

#include <memory>


namespace cmaterial::component {
    class CreatorButton : public IComponent {
        std::vector<std::unique_ptr<IComponent>> spawnedWindows;
        Framework* app_context;

    public:
        CreatorButton(Framework* app) : app_context(app) {}

        void render(ImGuiIO *io) override {
            if (ImGui::Button("Spawn Window")) {
                auto newWin = std::make_unique<BasicWindow>();
                newWin->name = "Dynamic " + std::to_string(spawnedWindows.size());

                app_context->addComponent(newWin.get());

                spawnedWindows.push_back(std::move(newWin));
            }

            std::erase_if(spawnedWindows, [](const auto& win) {
                return win->isDead;
            });
        }
    };
}



#endif //CMATERIAL_CREATORBUTTON_H
