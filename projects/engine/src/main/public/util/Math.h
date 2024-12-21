#pragma once

#include <flecs.h>
#include <glm/glm.hpp>
#include <components/3d/Components3d.h>

class Math {
public:
    static glm::mat4 computeWorldTransform(flecs::entity e) {
        glm::mat4 mat = e.get<Transform3d>()->value;
        auto parent = e.parent();
        if (parent && parent.has<Transform3d>()) {
            mat *= computeWorldTransform(parent);
        }
        return mat;
    }
};
