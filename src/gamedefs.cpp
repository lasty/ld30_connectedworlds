
#include "gamedefs.h"

#include <map>

bool CanCollide(const tile &td)
{
	switch (td)
	{
		case tile::none:
			return true;

		case tile::grass1:
		case tile::grass2:
		case tile::grass3:
		case tile::grass4:
			return false;

		case tile::cave1:
		case tile::cave2:
		case tile::cave3:
		case tile::cave4:
		case tile::cave5:
		case tile::cave6:
			return false;

		case tile::rock1:
		case tile::rock2:
			return true;

		default:
			return true;
	}
}


std::map<ent, std::string> NameMap = { {ent::none, "Nothing"}
	, { ent::player, "Player" }
	, { ent::coin, "Copper Coin" }
	, { ent::coin_gold, "Gold Coin" }
	, { ent::coin_silver, "Silver Coin" }
	, { ent::food, "Generic Food" }
	, { ent::food1, "C-Ration" }
	, { ent::food2, "Potato Salad" }
	, { ent::food3, "Roast Ham" }
	};



std::string & GetNameForEntity(ent e)
{
	return NameMap.at(e);
}

