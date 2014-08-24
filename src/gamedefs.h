#ifndef GAMEDEFS_H
#define GAMEDEFS_H

// enums for entities and tiles

enum class ent
{
	none,
	player,
	coin
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


};

bool CanCollide(const tile &td);



#endif // GAMEDEFS_H
