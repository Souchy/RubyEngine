#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>

struct UiTag {};

struct Boundingbox2d {
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
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

    // private:
    //     void setBB(GLint x, GLint y, GLsizei width, GLsizei height) {
    //         this->x = x;
    //         this->y = y;
    //         this->width = width;
    //         this->height = height;
    //     }
};
struct Fbo {
    GLuint id;
    GLuint texture;
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
    bool active;
    // GLuint depth;
    // GLuint stencil;

    // GLuint fbo;
    // GLuint texture;

    std::shared_ptr<Viewport> viewport;
};

class StretchViewport : public Viewport {
public:
    void resize(int width, int height) override {
        this->width = width;
        this->height = height;
    }
};
enum FitWay {
    Width,
    Height
};
enum FitMode {
    Stretch,
    Fit,
    Fill,
    Extend
};
class SomeViewport : public Viewport {
public:
    FitMode mode;
    void resize(int width, int height) override {
        float aspect = width / height;
        if (mode == FitMode::Fit) {
            // float scale = aspect > this->aspect ? width / this->width : height / this->height;
            // this->width = this->width * scale;
            // this->height = this->height * scale;
            if (aspect > this->aspect) {
                this->width = width;
                this->height = width / aspect;
            } else {
                this->height = height;
                this->width = height * aspect;
            }
        } else if (mode == FitMode::Fill) {
            // float scale = aspect < this->aspect ? width / this->width : height / this->height;
            // this->width = this->width * scale;
            // this->height = this->height * scale;
            if (aspect < this->aspect) {
                this->width = width;
                this->height = width / aspect;
            } else {
                this->height = height;
                this->width = height * aspect;
            }
        } else if (mode == FitMode::Stretch) {
            this->width = width;
            this->height = height;
        } else if (mode == FitMode::Extend) {
            this->width = width;
            this->height = height;
        }
    }
};
class FitViewport : public Viewport {
public:
    FitWay way;
    void resize(int width, int height) override {
        if (way == FitWay::Width) {
            this->width = width;
            this->height = width / aspect;

        } else {
            this->height = height;
            this->width = height * aspect;
        }
    }
};
class FillViewport : public Viewport {
public:
    FitWay way;
    void resize(int width, int height) override {
        // aspect = w/h
        // if(width > height) {
        //     this->width = width;
        //     this->height = width / aspect;
        // } else {
        //     this->height = height;
        //     this->width = height * aspect;
        // }
        // if(way == FitWay::Width) {
        //     this->width = width;
        //     this->height = width / aspect;
        // } else {
        //     this->height = height;
        //     this->width = height * aspect;
        // }
    }
};
class ExtendViewport : public Viewport {
public:
    FitWay way;
    void resize(int width, int height) override {
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
