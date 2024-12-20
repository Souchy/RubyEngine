#pragma once
#include <vector>
#include <glm/glm.hpp>

class Mesh {
public:
    std::vector<glm::uvec3> indices;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<glm::uvec3> colors; // GLfloat
    // std::vector<glm::vec3> tangents;
};
