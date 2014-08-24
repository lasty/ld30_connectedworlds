
#include "player.h"

#include "world.h"
#include "entity.h"

#include <memory>

#include <glm/vec2.hpp>
#include <glm/gtc/random.hpp>


void Player::Use()
{
	if(not GetAlive()) return;

	auto item = inv.PopFromSlot();

	if (item)
	{
		bool used = false;

		Food *f = dynamic_cast<Food*>(item.get());
		if (f)
		{
			used = Pickup(*f); //Eat(*f);
			world->sounds.UseItem();
			//used = true;
		}

		//TODO other kinds of useable objects

		if (not used)
		{
			SetMessage("I can't use this.");

			//just drop it, to save deleting it

			world->SpawnEntity(item);
			item->Shoot(position, look_at, 5);
			world->sounds.ErrorBeep();
		}

	}
	else
	{
		SetMessage("Nothing to use.");
		world->sounds.ErrorBeep();
	}
}

void Player::Throw()
{
	if(not GetAlive()) return;

	auto item = inv.PopFromSlot();

	const float throwspeed = 500.0f;

	if (item)
	{
		world->sounds.ThrowItem();
		world->SpawnEntity(item);

		if (glm::distance(position, look_at) > 5.0f)
		{
			//add some random variation
			float rx = glm::gaussRand(0.0f, 4.0f);
			float ry = glm::gaussRand(0.0f, 4.0f);
			glm::vec2 rand{rx, ry};

			item->Shoot(position, look_at+rand, throwspeed);

			//add our velocity
			item->velocity += velocity * 0.5f;
		}
		else
		{
			item->Shoot(position, look_at, throwspeed);

			//add our velocity
			item->velocity += velocity * 0.5f;
		}
	}
	else
	{
		SetMessage("Nothing to throw.");
		world->sounds.ErrorBeep();
	}
}


void Player::DropInv()
{
	for(auto &e : inv.items)
	{
		world->SpawnDie(e, position.x, position.y);
		e.reset();
	}
	inv.Clear();
}


void Player::HungerCheck(float dt)
{
	hunger -= hunger_per_second * dt;
	if (hunger < 0.0f)
	{

		if (big_timer < -0.5f)
		{
			BigMessage("Starving!", 1.0f);
			world->sounds.Hit();
		}

		hunger = 0.0f;
		health -= 5.0f * dt;
	}
}

void Player::HealthCheck(float dt)
{
	if (health < 0.0f)
	{
		if (StillAlive())
		{
			world->sounds.Explosion();
			DropInv();
			Kill();
		}
	}
	else if (health > 100.0f)
	{
		health -= 1.0f * dt;
	}
}


