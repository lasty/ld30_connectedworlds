#ifndef SHOP_H
#define SHOP_H


#include "entity.h"
#include "inventory.h"

#include <memory>

#include "font/text.h"
class Camera;
class World;

class ThingsWithInventory : public Entity
{
public:
	ThingsWithInventory(float x, float y)
	: Entity( ent::none, 64.0f )
	{
		position.x = x;
		position.y = y;

		inventory.reset(new Inventory());
		draw_circle = true;
	}

	std::string name = "ThingsWithInventory";

	std::unique_ptr<Text> text_above;
	std::unique_ptr<Text> text_below;

	void Render(const Camera &cam) const;

	void Update(float dt) override;

};


class SharedInvArea : public ThingsWithInventory
{
public:
	SharedInvArea(float x, float y)
	: ThingsWithInventory(x,y)
	{
		entitydef = ent::portal;

		name = "Shared Portal";


		delta_heading=360.0f;
	}

};



class Shop : public ThingsWithInventory
{
public:
	Shop(World &world, float x, float y, std::string sell, std::string spawn, int price)
	: ThingsWithInventory(x,y)
	, world(world)
	, selling_item(sell)
	, spawn_item(spawn)
	, price(price)
	{
		entitydef = ent::shop;
		name = "Shop";
	}

	World &world;

	std::string selling_item = "Nothing";
	std::string spawn_item = "nothing";

	int price = 99;

	bool CanPickup(std::shared_ptr<Entity> &e) override;

	void Update(float dt) override;

};



#endif // SHOP_H
