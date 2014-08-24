
#ifndef ITEMS_H
#define ITEMS_H

// Some more specific game entities

#include "entity.h"

#include "utils.h"

#include "gamedefs.h"

class Player;

class Coin : public Entity
{
public:
	Coin( float x, float y, int coin_type)
	: Entity( ent::coin, 20.0f )
	{
		position.x = x;
		position.y = y;
		heading = random_rotation();

		delta_heading = random_rot_velocity();

		if (coin_type == 0){ coin_value = 1; tint_colour = colour::copper; }
		else if (coin_type == 1) { coin_value = 10;  tint_colour = colour::silver; }
		else if (coin_type == 2) { coin_value = 100;  tint_colour = colour::gold; }
	}

	int coin_value = 0;

	void DispatchPickup(Player &player) override;
};



#endif // ITEMS_H
