#pragma once

#include <flecs.h>
#include <glm/glm.hpp>
#include <components/3d/Components3d.h>

class Math
{
public:
    /**
     * @brief Multiply the parent's transform with this entity's transform recursively
     * 
     * @param e 
     * @return glm::mat4 
     */
    static glm::mat4 computeWorldTransform(flecs::entity e)
    {
        glm::mat4 mat = e.get<Transform3d>()->getValue();
        auto parent = e.parent();
        if (parent && parent.has<Transform3d>()) {
            mat = computeWorldTransform(parent) * mat;
        }
        return mat;
    }
};
