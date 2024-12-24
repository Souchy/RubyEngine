#pragma once

#include <glm/glm.hpp>

struct Position {
	glm::vec3 value;
};
struct Velocity {
	glm::vec3 value;
};


struct Transform3d {
	glm::mat4 value;
};

struct WorldTransform3d {
	glm::mat4 value;
};


struct CameraView3d {
	glm::mat4 value;
};

struct CameraPerspective3d {
	glm::mat4 value;
};

struct Camera3d {
	glm::vec3 pos;
	glm::mat4 view;
	glm::mat4 projection;
};

class Camera {
public:
	glm::vec3 pos;
	glm::mat4 view;
	glm::mat4 projection;
	float nearPlane;
	float farPlane;
	virtual void resize(int width, int height) = 0;
};

class CameraOrtho : public Camera {
public:
	float left;
	float right;
	float bottom;
	float top;
	void resize(int width, int height) override {
		// this->left = 0;
		// this->right = width;
		// this->bottom = 0;
		// this->top = height;
	}
};
class CameraPerspective : public Camera {
public:
	float fov;
	float aspect;
	void resize(int width, int height) override {
        // auto camPos = glm::vec3(0, 5, 10);
        // auto camTarget = glm::vec3(0.0f);
        // auto camUp = glm::vec3(0.0f, 1.0f, 0.0f);
        // view = glm::lookAt(pos, camTarget, camUp);

        // float fov = glm::radians(45.0f);
		// aspect = 16.f / 9.f
		// aspect =  (float) width / (float) height;
        projection = glm::perspective(fov, aspect, nearPlane, farPlane);
	}
};
