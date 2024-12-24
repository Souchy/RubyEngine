#pragma once

#include <glad/glad.h>

struct UiTag {};

struct Fbo {
	GLuint id;
	GLuint texture;
	GLuint x;
	GLuint y;
	GLuint width;
	GLuint height;
	// GLuint depth;
	// GLuint stencil;

    // GLuint fbo;
    // GLuint texture;
};


// struct WindowSize {
// 	unsigned int width;
// 	unsigned int height;
// };
