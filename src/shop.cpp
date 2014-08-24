
#include "shop.h"

#include "font/text.h"

#include "camera.h"

#include <sstream>


void ThingsWithInventory::Render(const Camera &cam) const
{
	glm::vec2 offset = cam.GetOffset();

	glm::vec2 pos = position - offset;

	if (text_above)
	{
		float w = text_above->GetWidth();
		float h = text_above->GetHeight();

		text_above->Render(pos.x - w/2, pos.y - radius - h);
	}

	if (text_below)
	{
		float w = text_below->GetWidth();
		//float h = text_below->GetHeight();

		text_below->Render(pos.x - w/2, pos.y + radius);
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
			ss << "Num Items: " << inventory->GetSize();
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
