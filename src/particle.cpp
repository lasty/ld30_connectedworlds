
#include "particle.h"

#include "sprite.h"


#include <glm/geometric.hpp>


Particle::Particle(Sprite & sprite, float x, float y, float angle)
: sprite(&sprite)
, position(x, y)
, velocity(0.0f, 0.0f)
, angle(angle)
{ }


void Particle::Render() const
{
	sprite->Render((int)position.x, (int)position.y, angle);
}

void Particle::Update(float dt)
{
	position += velocity * dt;
	angle += angle_velocity * dt;

	if (ttl > 0.0f)
	{
		ttl -= dt;
		if (ttl <= 0.0f) alive = false;
	}

	if (friction >= 0.0f)
	{
		float fr = (1.0f - (friction * dt));

		velocity *= fr;
	}
}

void Particle::Kill() { alive = false; }

// Simple circle collision detection,  If distance between is less than the
// two particle's radius, then they collide
bool Particle::HasCollision(const Particle &other) const
{
	float dist = glm::distance(position, other.position);
	dist -= radius;
	dist -= other.radius;

	return dist <= 0.0f;
}
