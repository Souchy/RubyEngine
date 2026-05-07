#pragma once

#include <shaders/Shader.h>

class Material {
public:
    Shader *shader;
    // parameters...
    GLenum MODE = GL_TRIANGLES;
    std::map<std::string, float> floats;
};

class ShaderParam {
public:
    std::string name;
    std::string type;
};

class ShaderParameter {
public:
    std::string name;
};
class ShaderParameterFloat : public ShaderParameter {
public:
    float value;
};
class ShaderParameterVec3 : public ShaderParameter {
public:
    glm::vec3 value;
};
class ShaderParameterMat4 : public ShaderParameter {
public:
    glm::mat4 value;
};
class ShaderParameterTexture : public ShaderParameter {
public:
    GLuint value;
};
class ShaderParameterInt : public ShaderParameter {
public:
    int value;
};
class ShaderParameterBool : public ShaderParameter {
public:
    bool value;
};
class ShaderParameterSampler2D : public ShaderParameter {
public:
    GLuint value;
};
