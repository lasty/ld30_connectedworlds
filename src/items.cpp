
#include "items.h"

#include "player.h"


void Coin::DispatchPickup(Player &player) { player.PickupActual(*this); }

void Food::DispatchPickup(Player &player) { player.PickupActual(*this); }


