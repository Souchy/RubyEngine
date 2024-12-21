#pragma once

#include <glm/glm.hpp>
#include <vector>

class Mesh {
public:
    // GLuint meshType; // GL_TRIANGLES, GL_STRIP,  GL_FAN?, GL_LINES, GL_POINTS..
    std::vector<glm::uvec3> indices;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec4> colors; // GLfloat
    // std::vector<glm::vec3> tangents;
};
