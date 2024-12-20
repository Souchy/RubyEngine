#include <array>
#include <iostream>
#include <vector>
#include "resources/Mesh.h"

class Cube {
public:
    static Mesh *generate() {
        Mesh *mesh = new Mesh();
		// positions
        mesh->positions = {
			// front (or back?) face
            glm::vec3(-1, -1, -1), 	// 0
            glm::vec3(1, -1, -1), 	// 1
            glm::vec3(1, 1, -1), 	// 2
            glm::vec3(-1, 1, -1), 	// 3
			// back (or front?) face
            glm::vec3(-1, -1, 1), 	// 4
            glm::vec3(1, -1, 1), 	// 5
            glm::vec3(1, 1, 1), 	// 6
            glm::vec3(-1, 1, 1) 	// 7
        };
		// normals
        mesh->normals = {
            glm::vec3(0, 0, 1),
            glm::vec3(1, 0, 0),
            glm::vec3(0, 0, -1),
            glm::vec3(-1, 0, 0),
            glm::vec3(0, 1, 0),
            glm::vec3(0, -1, 0) //
        };
		// 12 triangles : 6 faces * 2 triangles each
		mesh->indices = {
            glm::uvec3(0, 1, 3),   
			glm::uvec3(3, 1, 2),
            glm::uvec3(1, 5, 2),   
			glm::uvec3(2, 5, 6),
            glm::uvec3(5, 4, 6),   
			glm::uvec3(6, 4, 7),
            glm::uvec3(4, 0, 7),   
			glm::uvec3(7, 0, 3),
            glm::uvec3(3, 2, 7),   
			glm::uvec3(7, 2, 6),
            glm::uvec3(4, 5, 0),   
			glm::uvec3(0, 5, 1)
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
			// front (or back?) face
            glm::vec4(0, 0, 0, 1), 	// 0
            glm::vec4(1, 0, 0, 1), 	// 1
            glm::vec4(1, 1, 0, 1), 	// 2
            glm::vec4(0, 1, 0, 1), 	// 3
			// back (or front?) face
            glm::vec4(0, 0, 1, 1), 	// 4
            glm::vec4(1, 0, 1, 1), 	// 5
            glm::vec4(1, 1, 1, 1), 	// 6
            glm::vec4(0, 1, 1, 1) 	// 7
        };
        return mesh;
    }
};
