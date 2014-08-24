
#include "player.h"

#include "world.h"
#include "entity.h"

#include <memory>

#include <glm/vec2.hpp>
#include <glm/gtc/random.hpp>


void Player::Use()
{
	auto item = inv.PopFromSlot();

	if (item)
	{
		world->sounds.UseItem();
		//world->SpawnEntity(item);
		//item->Shoot(position, look_at, 100);
	}
	else
	{
		world->sounds.ErrorBeep();
	}
}

void Player::Throw()
{
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
		world->sounds.ErrorBeep();
	}
}


