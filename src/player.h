#ifndef PLAYER_H
#define PLAYER_H

// Class to control the player with

#include "entity.h"

#include <glm/vec2.hpp>
#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>


#include <iostream>

class Player : public Entity
{
public:
	Player(World &theworld)
	: Entity(ent::player, 16.0f)
	{
		world = &theworld;

		friction = 0.9f;
		position.x = 50;
		position.y = 50;
	}

	bool turning_left = false;
	bool turning_right = false;
	bool thrusting = false;


	void Update(float dt)
	{
		const float turnrate = 200.0f;
		const float thrustrate = 800.0f;
		if (turning_left) heading -= dt * turnrate;
		if (turning_right) heading += dt * turnrate;

		if (thrusting)
		{
			float rangle = glm::radians(heading - 90.0f);  //90 degrees off, sprite points up

			// convert heading to vec2
			glm::vec2 thrustvec { glm::cos(rangle) , glm::sin(rangle) };

			thrustvec = glm::normalize(thrustvec) * thrustrate * dt;
			velocity += thrustvec;
		}

		Entity::Update(dt);
	}

};


#endif // PLAYER_H
