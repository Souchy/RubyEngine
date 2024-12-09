#pragma once

#include "../Node.h"
// #include <glm/matrix_float4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Node3d : public Node {
public:
    glm::mat4 getTransform() const {
        return _transform;
    }
	glm::mat4 getWorldTransform() const {
        glm::mat4 mat = _transform;
		// Node3d* parent3d = dynamic_cast<Node3d*>(parent);
        // if (parent3d != nullptr)
        // {
        //     mat *= parent3d->getWorldTransform();
        // }
		return mat;
	}

protected:
    glm::mat4 _transform = glm::mat4(1.0f);
};
