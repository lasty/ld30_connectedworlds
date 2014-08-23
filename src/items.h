
#ifndef ITEMS_H
#define ITEMS_H

// Some more specific game entities

#include "entity.h"

#include "utils.h"

#include "gamedefs.h"


class Coin : public Entity
{
public:
	Coin( float x, float y, float rotation)
	: Entity( ent::coin, 20.0f )
	{
		position.x = x;
		position.y = y;
		heading = rotation;

		delta_heading = random_rot_velocity();
	}
};



#endif // ITEMS_H
