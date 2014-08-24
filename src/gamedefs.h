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
	white,
	grey,
	silver,
	copper,
	gold
};

bool CanCollide(const tile &td);



#endif // GAMEDEFS_H
