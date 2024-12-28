#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <array>

struct Position
{
	glm::vec3 value = glm::vec3(0.0f);
};
struct Scale
{
	glm::vec3 value = glm::vec3(1.0f);
};
struct Rotation
{
	glm::vec3 value = glm::vec3(0.0f);
};
struct Velocity
{
	glm::vec3 value;
};

class Transform3d
{
public:
	void setPosition(glm::vec3 position)
	{
		this->position = position;
		update();
	}
	void setRotation(glm::vec3 rotation)
	{
		this->rotation = rotation;
		update();
	}
	void setScale(glm::vec3 scale)
	{
		this->scale = scale;
		update();
	}
	glm::vec3 getPosition() const
	{
		return position;
	}
	glm::vec3 getRotation() const
	{
		return rotation;
	}
	glm::vec3 getScale() const
	{
		return scale;
	}
	glm::mat4 getValue() const
	{
		return value;
	}
	std::array<float, 3> getPositionArray() const
	{
		return {position.x, position.y, position.z};
	}
	std::array<float, 3> getRotationArray() const
	{
		return {rotation.x, rotation.y, rotation.z};
	}
	std::array<float, 3> getScaleArray() const
	{
		return {scale.x, scale.y, scale.z};
	}
	void setPositionArray(const std::array<float, 3>& p)
	{
		setPosition(glm::vec3(p[0], p[1], p[2]));
	}
	void setRotationArray(const std::array<float, 3>& p)
	{
		setRotation(glm::vec3(p[0], p[1], p[2]));
	}
	void setScaleArray(const std::array<float, 3>& p)
	{
		setScale(glm::vec3(p[0], p[1], p[2]));
	}
private:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
	glm::mat4 value = glm::mat4(1.0f);
	void update() {
		auto mat = glm::mat4(1.0f);
		mat = glm::translate(mat, position);
		mat = glm::scale (mat, scale);
		mat = glm::rotate(mat, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		mat = glm::rotate(mat, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::rotate(mat, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		this->value = mat;
	}
};

struct WorldTransform3d
{
	glm::mat4 value;
};

struct CameraView3d
{
	glm::mat4 value;
};

struct CameraPerspective3d
{
	glm::mat4 value;
};

struct Camera3d
{
	glm::vec3 pos;
	glm::mat4 view;
	glm::mat4 projection;
};

class Camera
{
public:
	glm::vec3 pos;
	glm::mat4 view;
	glm::mat4 projection;
	float nearPlane;
	float farPlane;
	virtual void resize(int width, int height) = 0;
};

class CameraOrtho : public Camera
{
public:
	float left;
	float right;
	float bottom;
	float top;
	void resize(int width, int height) override
	{
		// this->left = 0;
		// this->right = width;
		// this->bottom = 0;
		// this->top = height;
	}
};
class CameraPerspective : public Camera
{
public:
	float fov;
	float aspect;
	void resize(int width, int height) override
	{
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
