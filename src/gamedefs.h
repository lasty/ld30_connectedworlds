#ifndef GAMEDEFS_H
#define GAMEDEFS_H

#include <string>

// enums for entities and tiles

enum class ent
{
	none,
	player,
	coin,
	coin_gold,
	coin_silver,
	food,
	food1,
	food2,
	food3
};


enum class tile
{
	none,
	grass,
	dirt,
	stone,
	ore
};

enum class colour
{
	//default
	white,

	//
	grey,

	//coins
	silver,
	copper,
	gold,

	// player colours
	blue,
	red

	, deadred


};

bool CanCollide(const tile &td);

std::string & GetNameForEntity(ent e);


#endif // GAMEDEFS_H
