#ifndef CAMERA_H
#define CAMERA_H

//simple 2d tracking camera

#include "entity.h"

#include <glm/vec2.hpp>

class Camera
{
public:
	Camera(glm::vec2 dimensions, glm::vec2 startpos)
	: current_lookat(startpos)
	, set_lookat(startpos)
	, size(dimensions)
	, size_half(size/2.0f)
	{ }

	glm::vec2 current_lookat;
	glm::vec2 set_lookat;
	glm::vec2 size;
	glm::vec2 size_half;

	void Follow(glm::vec2 pos) { set_lookat = pos; }
	void Follow(const Entity &e) { Follow(e.position); }

	glm::vec2 GetTopLeft() const { return GetPosition() - size_half; }
	glm::vec2 GetBottomRight() const { return GetPosition() + size_half; }
	const glm::vec2 & GetPosition() const { return current_lookat; }
	glm::vec2 GetOffset() const { return GetPosition() - size_half; }
	const glm::vec2 & GetSize() const { return size; }

	void SetTransition(glm::vec2 offset)
	{
		current_lookat += offset;
	}

	void Update(float dt)
	{
		float interp = dt * 10.0f;
		interp = glm::clamp(interp, 0.0f, 1.0f);
		current_lookat = glm::mix(current_lookat, set_lookat, interp);
	}
};

#endif // CAMERA_H

