#include "resources/Mesh.h"
#include <array>
#include <iostream>
#include <vector>

class Cube {
public:
    static Mesh *generate() {
        Mesh *mesh = new Mesh();
        // 12 triangles : 6 faces * 2 triangles each
        mesh->indices = {
            // back
            glm::uvec3(0, 1, 3), // ccw
            glm::uvec3(3, 1, 2), //
            // right
            glm::uvec3(1, 5, 2), //
            glm::uvec3(2, 5, 6),
            // front
            glm::uvec3(5, 4, 6),
            glm::uvec3(6, 4, 7),
            // left
            glm::uvec3(4, 0, 7),
            glm::uvec3(7, 0, 3),
            // top
            glm::uvec3(3, 2, 7),
            glm::uvec3(7, 2, 6),
            // bottom
            glm::uvec3(4, 5, 0),
            glm::uvec3(0, 5, 1)
        };
        // positions
        mesh->positions = {
            // back face
            glm::vec3(-1, -1, -1), // 0  bottom left
            glm::vec3(1, -1, -1),  // 1  bottom right
            glm::vec3(1, 1, -1),   // 2  up right
            glm::vec3(-1, 1, -1),  // 3  up left
            // front face
            glm::vec3(-1, -1, 1),  // 4  bottom left
            glm::vec3(1, -1, 1),   // 5  bottom right
            glm::vec3(1, 1, 1),    // 6  up right
            glm::vec3(-1, 1, 1)    // 7  up left
        };
        // normals: 6 faces, based on indexed triangles
        mesh->normals = {
            glm::vec3(0, 0, -1), // back
            glm::vec3(1, 0, 0),  // right
            glm::vec3(0, 0, 1),  // front
            glm::vec3(-1, 0, 0), // left
            glm::vec3(0, 1, 0),  // top
            glm::vec3(0, -1, 0)  // bottom
        };
        // UVs for one face
        mesh->uvs = {
            glm::vec2(0, 0),
            glm::vec2(1, 0),
            glm::vec2(1, 1),
            glm::vec2(0, 1) //
        };
        // colors per vertex
        mesh->colors = {
            // back face
            glm::vec4(0, 0, 0, 1), // 0
            glm::vec4(1, 0, 0, 1), // 1
            glm::vec4(1, 1, 0, 1), // 2
            glm::vec4(0, 1, 0, 1), // 3
            // front face
            glm::vec4(0, 0, 1, 1), // 4
            glm::vec4(1, 0, 1, 1), // 5
            glm::vec4(1, 1, 1, 1), // 6
            glm::vec4(0, 1, 1, 1)  // 7
        };
        return mesh;
    }
};
