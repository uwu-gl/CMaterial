//
// Created by Earth_Studio on 2026/4/15.
//

#include "IComponent.h"

namespace cmaterial::component {
    void IComponent::addComponent(IComponent *component) {
        if (component == nullptr)
            return;

        if (component->name.empty())
            return;

        components.insert({component->name, component});
    }

    bool IComponent::getIsDead() {
        return isDead;
    }
}