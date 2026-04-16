//
// Created by Earth_Studio on 2026/4/12.
//

#include "content/component/BasicButton/BasicButton.h"
#include "content/component/BasicWindow/BasicWindow.h"
#include "content/component/CreatorButton/CreatorButton.h"
#include "engine/framework/Framework.h"

int main() {
    cmaterial::Framework app;
    app.initialize();

    cmaterial::component::BasicWindow window1;
    window1.name = "window1";
    cmaterial::component::BasicWindow window2;
    window2.name = "window2";

    cmaterial::component::BasicButton button1;
    button1.name = "buttonInWindow1";
    cmaterial::component::CreatorButton button2 = cmaterial::component::CreatorButton(&app);
    button2.name = "buttonInWindow2";

    app.addComponent(&window1);
    window1.addComponent(&button1);

    app.addComponent(&window2);
    window2.addComponent(&button2);

    app.run();
    return 0;
}