
#include "shop.h"

#include "font/text.h"

#include "camera.h"
#include "world.h"

#include <sstream>


void ThingsWithInventory::Render(const Camera &cam) const
{
	glm::vec2 offset = cam.GetOffset();

	glm::vec2 pos = position - offset;

	if (text_above)
	{
		float xx = pos.x - text_above->GetWidth()/2;
		float yy = pos.y - radius - text_above->GetHeight();

		if (xx > 0 and yy > 0) //because of text auto positioning
		{
			text_above->Render(xx, yy);
		}
	}

	if (text_below)
	{
		float xx = pos.x - text_below->GetWidth()/2;
		float yy = pos.y + radius;


		if (xx > 0 and yy > 0) //because of text auto positioning
		{
			text_below->Render(xx, yy);
		}
	}

}


void ThingsWithInventory::Update(float dt)
{
	if (text_above)
	{
		text_above->SetText(name);
	}

	if (text_below)
	{
		std::stringstream ss;
		if (inventory)
		{
			ss << inventory->GetSize() << " Items";

			int money = inventory->CountCoins();
			if(money)
			{
				ss << " - " << FormatMoney(money);
			}
		}
		else
		{
			ss << "No inventory";
		}
		text_below->SetText(ss.str());
	}

	draw_circle = not draw_circle;//true;

/*
	if(inventory)
	{
		for(auto &i : inventory->items)
		{
			i->Update(dt);
		}
	}
*/

}



bool Shop::CanPickup(std::shared_ptr<Entity> &e)
{
	Coin *c = dynamic_cast<Coin*>(e.get());
	return c;
}



void Shop::Update(float dt)
{
	if (text_above)
	{
		std::stringstream ss;
		ss << selling_item << "  Shop  " << FormatMoney(price);

		text_above->SetText(ss.str());
	}

	int money = inventory->CountCoins();

	if (text_below)
	{
		std::stringstream ss;
		if (inventory)
		{
			ss << FormatMoney(money);
		}
		else
		{
			ss << "No inventory";
		}
		text_below->SetText(ss.str());
	}

	draw_circle = true;


	if (money >= price)
	{
		world.SpawnShopEntity(spawn_item, position.x, position.y);
		inventory->Clear();  //XXX No change!
	}
}


