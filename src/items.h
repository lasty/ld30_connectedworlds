
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
	Coin( float x, float y)
	: Entity( ent::coin, 11.0f )
	{
		position.x = x;
		position.y = y;
		heading = random_rotation();

		delta_heading = random_rot_velocity();

	}

	int coin_value = 0;

	void DispatchPickup(Player &player) override;
};


class Coin_Cent : public Coin
{
public:
	Coin_Cent(float x, float y)
	: Coin(x, y)
	{
		coin_value = 1;
		tint_colour = colour::copper;
		entitydef = ent::coin;
	}
};

class Coin_Silver : public Coin
{
public:
	Coin_Silver(float x, float y)
	: Coin(x, y)
	{
		coin_value = 10;
		tint_colour = colour::silver;
		entitydef = ent::coin_silver;
	}
};

class Coin_Gold : public Coin
{
public:
	Coin_Gold(float x, float y)
	: Coin(x, y)
	{
		radius = 13.0f;
		coin_value = 100;
		tint_colour = colour::gold;
		entitydef = ent::coin_gold;
	}
};


class Food : public Entity
{
public:
	Food( float x, float y)
	: Entity( ent::food, 13.0f )
	{
		position.x = x;
		position.y = y;
		heading = random_float(-15.0f, 15.0f);

		//delta_heading = random_rot_velocity();
	}

	int food_value = 0;

	void DispatchPickup(Player &player) override;
};


class Food_Ration : public Food
{
public:
	Food_Ration(float x, float y)
	: Food(x, y)
	{
		entitydef = ent::food1;
		food_value = 10;
	}
};


class Food_PotatoSalad : public Food
{
public:
	Food_PotatoSalad(float x, float y)
	: Food(x, y)
	{
		entitydef = ent::food2;
		food_value = 50;
	}
};


class Food_Roast : public Food
{
public:
	Food_Roast(float x, float y)
	: Food(x, y)
	{
		entitydef = ent::food3;
		food_value = 100;
	}
};


#endif // ITEMS_H
