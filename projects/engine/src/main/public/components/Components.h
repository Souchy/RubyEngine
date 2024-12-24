#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

struct UiTag {};

struct Fbo {
    GLuint id;
    GLuint texture;
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
    // GLuint depth;
    // GLuint stencil;

    // GLuint fbo;
    // GLuint texture;
};

struct WindowSize {
    unsigned int width;
    unsigned int height;
};

class Viewport {
public:
    // Camera3d *camera;
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
    bool aspectFixed;
    float aspect;
    glm::vec4 clearColor;
    // Transform3d transform;
    virtual void resize(int width, int height) = 0;
};

class StretchViewport : public Viewport {
public:
    void resize(int width, int height) override {
        this->width = width;
        this->height = height;
    }
};

class PercentViewport : public Viewport {
public:
    float xPercentOfWidth;
    float yPercentOfHeight;
    float widthPercentOfWidth;
    float heightPercentOfHeight;
    void resize(int width, int height) override {
        this->x = xPercentOfWidth * width;
        this->y = yPercentOfHeight * height;
        this->width = widthPercentOfWidth * width;
        this->height = heightPercentOfHeight * height;

        // if (aspectFixed) {
        // 	this->width = this->height * aspect;
        // }
        // // Fit
        // if(true) {

        // }
        // // Fill
        // if(true) {

        // }
        // // Extend
        // if(true) {

        // }
    }
};
