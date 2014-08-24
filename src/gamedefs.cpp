
#include "gamedefs.h"

#include <map>

bool CanCollide(const tile &td)
{
	switch (td)
	{
		case tile::none:
		case tile::ore:
			return true;

		case tile::stone:
		case tile::grass:
		case tile::dirt:
			return false;

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

