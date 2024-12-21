#pragma once

#include "resources/Mesh.h"
#include <array>
#include <iostream>
#include <vector>

class Gizmo {
public:
    static Mesh *generate() {
        Mesh *mesh = new Mesh();
		// pos
        mesh->positions.push_back(glm::vec3(0, 0, 0));
        mesh->positions.push_back(glm::vec3(1, 0, 0));
        mesh->positions.push_back(glm::vec3(0, 1, 0));
        mesh->positions.push_back(glm::vec3(0, 0, 1));
		// indices
        mesh->indices.push_back(glm::vec3(0, 1, 0));
        mesh->indices.push_back(glm::vec3(0, 2, 0));
        mesh->indices.push_back(glm::vec3(0, 3, 0));
		// normals
        mesh->normals.push_back(glm::vec3(1, 0, 0));
        mesh->normals.push_back(glm::vec3(1, 0, 0));
        mesh->normals.push_back(glm::vec3(0, 1, 0));
        mesh->normals.push_back(glm::vec3(0, 0, 1));
		// colors
        mesh->colors = {
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), // (Center)
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), // Red (X-axis)
            glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), // Green (Y-axis)
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)  // Blue (Z-axis)
        };
        return mesh;
    }
};
