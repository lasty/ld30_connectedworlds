#ifndef ENTITY_H
#define ENTITY_H


#include "gamedefs.h"

#include <memory>

#include <glm/vec2.hpp>

class World;
class Player;
class Inventory;

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

	bool apply_friction = true;
	float friction = 500.0f;  //simulate friction
	float ttl=0.0f; //time to live (for particle effects)
	float radius = 32.0f;

	float cooldown = 0.5f;

	bool draw_circle = false;

	colour tint_colour = colour::white;

	std::unique_ptr<Inventory> inventory;
	bool HasInventory() const { return bool(inventory); }


private:
	bool alive = true;

public:
	void Render() const;

	virtual void Update(float dt);

	void Kill();
	void Revive() { alive = true; }
	bool StillAlive() const { return alive; }

	bool HasCollision(const Entity &other) const;
	bool HasCollision(float x1, float x2, float y1, float y2) const;

	bool HasCollision(const World &world) const;
	bool HasMapCollision(const World &world, int x, int y) const;
	//bool HasCollision(const std::vector<Entity> &entities) const;

	const glm::vec2 & GetWorldPos() const { return position; }

	bool DrawCircle() const { return draw_circle; }

	void SetCooldown(float c = 0.5f) { cooldown = c; }
	bool CanBePickedUp() const { return (not HasInventory()) and cooldown <= 0.0f ; }

	virtual bool CanPickup(std::shared_ptr<Entity> &e);
	virtual void Pickup(std::shared_ptr<Entity> &e);

	void Shoot(glm::vec2 from, glm::vec2 to, float speed);

	virtual void DispatchPickup(Player &player);

};


#endif // ENTITY_H
