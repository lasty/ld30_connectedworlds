
#include "gamedefs.h"


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

