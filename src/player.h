#ifndef PLAYER_H
#define PLAYER_H

// Class to control the player with

#include "entity.h"

#include "inventory.h"

#include "font/text.h"

#include "camera.h"

#include <glm/vec2.hpp>
#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>


class World;

#include <iostream>
#include <memory>
#include <sstream>


class Player : public Entity
{
public:
	Player(World &theworld)
	: Entity(ent::player, 18.0f)
	{
		world = &theworld;

		friction = 800.0f;
		apply_friction = true;

		static int id_stat = 0;
		id = id_stat++;

		if (id == 0) tint_colour = colour::blue;
		if (id == 1) tint_colour = colour::red;

		Reset();
	}

	int id = -1;

	float health = 100.0f;

	float hunger = 0.0f;
	float hunger_max = 100.0f;
	float hunger_per_second = 0.3f;

	Inventory inv;


	glm::vec2 control_stick;
	glm::vec2 look_at;
	float current_speed = 0.0f;
	float thrust_speed = 1600.0f;
	float max_speed = 400.0f;
	float rot_speed = 720.0f;

	//bool running = false;
	float walk_timer_legs = 0.0f;
	float walk_timer_arms = 0.0f;


	std::unique_ptr<Text> msg_text;
	std::unique_ptr<Text> big_text;

	float msg_timer = 0.0f;;
	float big_timer = 0.0f;;


	void SetMessage(std::string msg, float time = 1.0f)
	{
		if (msg_text)
		{
			msg_text->SetText(msg);
		}
		else
		{
			std::cout << msg << std::endl;
		}
		msg_timer = time;
	}


	void BigMessage(std::string msg, float time = 10.0f)
	{
		if (big_text)
		{
			big_text->SetText(msg);
		}
		else
		{
			std::cout << "** " << msg << std::endl;
		}
		big_timer = time;
	}

	void RenderText(const Camera &cam) const
	{
		if (big_text and big_timer > 0)
		{
			glm::vec2 pos = position - cam.GetOffset();
			pos.x -= big_text->GetWidth() / 2;
			pos.y -= 70;

			big_text->Render(pos.x, pos.y);
		}

		if (msg_text and msg_timer > 0)
		{
			glm::vec2 pos = position - cam.GetOffset();
			pos.x -= msg_text->GetWidth() / 2;
			pos.y -= 30;


			msg_text->Render(pos.x, pos.y);
		}
	}

	void Reset()
	{
		Revive();

		if (id == 0)
		{
			health = 100.0f;
			hunger = 20.0f;
		}
		else
		{
			health = 100.0f;
			hunger = 40.0f;
		}

		inv.Clear();

		position = { 0.0f, -40.0f };
		velocity = { 0.0f, 0.0f };

		msg_timer = 0.0f;
		big_timer = 0.0f;
	}

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

	void HungerCheck(float dt);
	void HealthCheck(float dt);

	void Update(float dt) override
	{
		float lookangle = VecToAngle(position, look_at);

		if (GetAlive())
		{
			heading = InterpAngle(heading, lookangle, dt * rot_speed);
		}
		else
		{
			BigMessage("Dead", 1.0f);
			SetMessage("(Press TAB to switch, or N for new game)", 1.0f);
			control_stick = {0.0f, 0.0f};
		}

		if (control_stick.x != 0 or control_stick.y != 0)
		{
			apply_friction = false;
			glm::vec2 thrustvec = glm::normalize(control_stick) * thrust_speed * dt;

			velocity += thrustvec;

			walk_timer_legs += dt * 7.0f;
			walk_timer_arms += dt * 7.1f;;
		}
		else
		{
			/*float vel = glm::length(velocity);
			walk_timer_legs = vel;
			walk_timer_arms = vel;
			*/
			walk_timer_legs = 0.0f;
			walk_timer_arms = 0.0f;


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


		HungerCheck(dt);

		HealthCheck(dt);



		msg_timer -= dt;
		big_timer -= dt;

	}

	void DropInv();

	bool CanPickup(std::shared_ptr<Entity> &e)
	{
		if (not GetAlive()) return false;
		if (inv.CanPickup(e))
		{
			return true;
		}
		else
		{
			if (msg_timer < -0.5f)
			{
				SetMessage("Inventory Full.", 1.0f);
			}
			return false;
		}
	}

	void Pickup(Entity &e)
	{
		//Double Dispatch pattern
		e.DispatchPickup(*this);
	}

	void Pickup(Coin &c)
	{
		//coins += c.coin_value;
		//BigMessage("COIN!!!", 1.0f);
	}

	bool Pickup(Food &f)
	{
		//coins += c.coin_value;
		if (hunger < hunger_max)
		{
			std::stringstream msg;
			msg << GetNameForEntity(f.entitydef) << "  (Food: " << f.food_value <<")";

			BigMessage("Yum!", 2.0f);
			SetMessage(msg.str(), 2.0f);

			health += f.food_value;

			hunger+= f.food_value;
			return true;
		}
		else
		{
			BigMessage("I'm Full", 2.0f);
			return false;
		}
	}


	void Pickup(std::shared_ptr<Entity> e);


	int GetAlive() const
	{
		return (health > 0.0f);
	}

	int GetCash() const
	{
		return inv.CountCoins();
	}

	int GetHungerPercent() const
	{
		return hunger * 100 / hunger_max;
	}

	int GetHealthPercent() const
	{
		return health;
	}

	Inventory & GetInventory() { return inv; }
	const Inventory & GetInventory() const { return inv; }

	void Use();

	void Throw();

};


#endif // PLAYER_H
