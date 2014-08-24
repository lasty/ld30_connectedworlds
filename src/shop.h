#ifndef SHOP_H
#define SHOP_H


#include "entity.h"
#include "inventory.h"

#include <memory>

#include "font/text.h"
class Camera;

class ThingsWithInventory : public Entity
{
public:
	ThingsWithInventory(float x, float y)
	: Entity( ent::none, 64.0f )
	{

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
		name = "SharedArea";
	}

};



class Shop : public ThingsWithInventory
{
public:
	Shop(float x, float y)
	: ThingsWithInventory(x,y)
	{
		name = "Shop";
	}

};



#endif // SHOP_H
