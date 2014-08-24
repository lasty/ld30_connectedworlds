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
	: Entity(ent::player, 24.0f)
	{
		world = &theworld;

		friction = 800.0f;
		apply_friction = true;
		position.x = 50;
		position.y = 50;

		static int id_stat = 0;
		id = id_stat++;
	}

	int id = -1;

	glm::vec2 control_stick;
	glm::vec2 look_at;
	float current_speed = 0.0f;
	float thrust_speed = 1600.0f;
	float max_speed = 400.0f;
	float rot_speed = 720.0f;

	//bool running = false;

	void SetMoveDirection(float x, float y)
	{
		control_stick = {x, y};
	}

	void SetMoveDirectionX(float x)
	{
		control_stick.x = x;
	}

	void SetMoveDirectionY(float y)
	{
		control_stick.y = y;
	}

	void SetLookAt(float x, float y)
	{
		look_at = {x, y};
	}

	void LostFocus()
	{
		control_stick = {0.0f, 0.0f};
		//running = false;
	}

	float VecToAngle(const glm::vec2 &from, const glm::vec2 &to)
	{
		glm::vec2 delta = from - to;
		float rad = atan2(delta.y, delta.x);
		return NormalizeAngle(glm::degrees(rad) - 90.0f);
	}

	float NormalizeAngle(float d)
	{
		while(d <= 180.0f) { d += 360.0f; }
		while(d > 180.0f) { d -= 360.0f; }

		return d;
	}

	float AngleDiff(float from, float to)
	{
		float d = NormalizeAngle(from) - NormalizeAngle(to);
		return NormalizeAngle(d);
	}

	float InterpAngle(float from, float to, float maxangle)
	{
		float d1 = AngleDiff(from, to);
		float d2 = AngleDiff(to, from);

		//if (id == 0) std::cout << "d1="<<d1<<"  d2="<<d2<< "  maxangle="<< maxangle <<std::endl;
		if (abs(d1) <= maxangle+1 or abs(d2) <= maxangle+1)
		return to;

		if (d1 > d2)
		{
			return NormalizeAngle(from - maxangle);
		}
		else
		{
			return NormalizeAngle(from + maxangle);
		}
	}


	void Update(float dt)
	{
		float lookangle = VecToAngle(position, look_at);

		heading = InterpAngle(heading, lookangle, dt * rot_speed);

		if (control_stick.x != 0 or control_stick.y != 0)
		{
			apply_friction = false;
			glm::vec2 thrustvec = glm::normalize(control_stick) * thrust_speed * dt;

			velocity += thrustvec;
		}
		else
		{
			apply_friction = true;
		}

		if (glm::length(velocity) > max_speed)
		{
			velocity = glm::normalize(velocity) * max_speed;
		}

		if (glm::length(velocity) < 1.0f)
		{
			velocity = {0.0f, 0.0f};
		}

		if (id == 0)
		{
			//std::cout << "Player " << id << " Rot: " << heading<< std::endl;
		}

		Entity::Update(dt);
	}

};


#endif // PLAYER_H
