#ifndef ENTITY_H
#define ENTITY_H


#include "gamedefs.h"

#include <glm/vec2.hpp>

class World;


class Entity
{
public:
	Entity() { }
	Entity(const ent &entitydef, float radius) : entitydef(entitydef), radius(radius) { }

	ent entitydef = ent::none;
	int data = 0;
	World *world = nullptr;

public:
	glm::vec2 position;
	glm::vec2 velocity;

	float heading = 0.0f;
	float delta_heading = 0.0f;

	bool apply_friction = false;
	float friction = 0.0f;  //simulate friction
	float ttl=0.0f; //time to live (for particle effects)
	float radius = 32.0f;

private:
	bool alive = true;

public:
	void Render() const;

	void Update(float dt);

	void Kill();

	bool HasCollision(const Entity &other) const;
	bool HasCollision(float x1, float x2, float y1, float y2) const;

	bool HasCollision(const World &world) const;
	bool HasMapCollision(const World &world, int x, int y) const;
	//bool HasCollision(const std::vector<Entity> &entities) const;

	const glm::vec2 & GetWorldPos() const { return position; }
};


#endif // ENTITY_H
