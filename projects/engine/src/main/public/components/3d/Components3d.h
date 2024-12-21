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
