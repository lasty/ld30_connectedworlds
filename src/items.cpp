
#include "items.h"

#include "player.h"


void Coin::DispatchPickup(Player &player) { player.Pickup(*this); }


