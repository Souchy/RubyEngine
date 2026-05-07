#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include <rttr/registration>

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
    RTTR_ENABLE()
public:
	Transform3d()
	{
		position = glm::vec3(0.0f);
		rotation = glm::vec3(0.0f);
		scale = glm::vec3(1.0f);
		update();
	}
	Transform3d(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
		update();
	}
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
	void setPositionArray(const std::array<float, 3> &p)
	{
		setPosition(glm::vec3(p[0], p[1], p[2]));
	}
	void setRotationArray(const std::array<float, 3> &p)
	{
		setRotation(glm::vec3(p[0], p[1], p[2]));
	}
	void setScaleArray(const std::array<float, 3> &p)
	{
		setScale(glm::vec3(p[0], p[1], p[2]));
	}

private:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
	glm::mat4 value = glm::mat4(1.0f);
	void update()
	{
		auto mat = glm::mat4(1.0f);
		mat = glm::translate(mat, position);
		mat = glm::scale(mat, scale);
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

RTTR_REGISTRATION
{
	rttr::registration::class_<Transform3d>("Transform3d")
		.property("position", &Transform3d::getPosition, &Transform3d::setPosition)
		.method("getPositionArray", &Transform3d::getPositionArray)
		.method("setPositionArray", &Transform3d::setPositionArray)
		.property("rotation", &Transform3d::getRotation, &Transform3d::setRotation)
		.method("getRotationArray", &Transform3d::getRotationArray)
		.method("setRotationArray", &Transform3d::setRotationArray)
		.property("scale", &Transform3d::getScale, &Transform3d::setScale)
		.method("getScaleArray", &Transform3d::getScaleArray)
		.method("setScaleArray", &Transform3d::setScaleArray);
		
	rttr::registration::class_<Transform3d*>("Transform3d*")
		.property("position", &Transform3d::getPosition, &Transform3d::setPosition)
		.method("getPositionArray", &Transform3d::getPositionArray)
		.method("setPositionArray", &Transform3d::setPositionArray)
		.property("rotation", &Transform3d::getRotation, &Transform3d::setRotation)
		.method("getRotationArray", &Transform3d::getRotationArray)
		.method("setRotationArray", &Transform3d::setRotationArray)
		.property("scale", &Transform3d::getScale, &Transform3d::setScale)
		.method("getScaleArray", &Transform3d::getScaleArray)
		.method("setScaleArray", &Transform3d::setScaleArray);
		// .property("value", &Transform3d::getValue);

	// rttr::registration::class_<Camera3d>("Camera3d")
	// 	.property("pos", &Camera3d::pos)
	// 	.property("view", &Camera3d::view)
	// 	.property("projection", &Camera3d::projection);
	// rttr::registration::class_<Camera>("Camera")
	// 	.property("pos", &Camera::pos)
	// 	.property("view", &Camera::view)
	// 	.property("projection", &Camera::projection)
	// 	.property("nearPlane", &Camera::nearPlane)
	// 	.property("farPlane", &Camera::farPlane);
	// rttr::registration::class_<CameraOrtho>("CameraOrtho")
	// 	.property("left", &CameraOrtho::left)
	// 	.property("right", &CameraOrtho::right)
	// 	.property("bottom", &CameraOrtho::bottom)
	// 	.property("top", &CameraOrtho::top);
	// rttr::registration::class_<CameraPerspective>("CameraPerspective")
	// 	.property("fov", &CameraPerspective::fov)
	// 	.property("aspect", &CameraPerspective::aspect);
	// rttr::registration::class_<Position>("Position")
	// 	.property("value", &Position::value);
	// rttr::registration::class_<Scale>("Scale")
	// 	.property("value", &Scale::value);
	// rttr::registration::class_<Rotation>("Rotation")
	// 	.property("value", &Rotation::value);
	// rttr::registration::class_<Velocity>("Velocity")
	// 	.property("value", &Velocity::value);
	// rttr::registration::class_<WorldTransform3d>("WorldTransform3d")
	// 	.property("value", &WorldTransform3d::value);
	// rttr::registration::class_<CameraView3d>("CameraView3d")
	// 	.property("value", &CameraView3d::value);
	// rttr::registration::class_<CameraPerspective3d>("CameraPerspective3d")
	// 	.property("value", &CameraPerspective3d::value);
}