#pragma once

#include <shaders/Shader.h>

class Material {
public:
    Shader *shader;
    // parameters...
    GLenum MODE = GL_TRIANGLES;
};
