#ifndef PARTICLE_H
#define PARTICLE_H

#include "sprite.h"

#include <glm/vec2.hpp>

// Instance class of sprites.  Has some simple physics and collission detection
// with other particles.

class Particle
{
public:
	Particle(Sprite & sprite, float x, float y, float angle);

public:
	bool alive = true;
	Sprite *sprite = nullptr;
	glm::vec2 position;
	glm::vec2 velocity;
	float angle;
	float angle_velocity;
	float friction = 0.0f;  //simulate friction
	float ttl=0.0f; //time to live (for particle effects)
	float radius = 32.0f;

public:
	void Render() const;

	void Update(float dt);

	void Kill();

	// Simple circle collision detection,  If distance between is less than the
	// two particle's radius, then they collide
	bool HasCollision(const Particle &other) const;

};


#endif // PARTICLE_H



