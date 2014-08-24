#ifndef HUD_H
#define HUD_H

#include "sdl/headers.h"
#include "sdl/renderer.h"
#include "font/font.h"
#include "font/text.h"

#include "gamedefs.h"
#include "utils.h"

#include "inventory.h"

#include <sstream>
#include <vector>

class GameApp;
class Camera;
class Player;

class InventorySlot
{
public:
	InventorySlot(sdl::Renderer &rend, Font &font, int slot_id)
	: renderer(rend), font(font), id(slot_id)
	, num_text(rend, font, "1")
	, name_text(rend, font, "Empty")
	, count_text(rend, font, "x 0")
	{
		yoffset = (5-id) * -40;
		yoffset -= 40;
		xoffset = 10;

		num_text.shadow = true;
		name_text.shadow = true;
		count_text.shadow = true;

		num_text.box = true;
		name_text.box = true;
		count_text.box = true;
	}

	sdl::Renderer &renderer;
	Font &font;
	int id;

	int count = 0;

	int yoffset = 0;
	int xoffset = 0;

	Text num_text;
	Text name_text;
	Text count_text;

	void SetInventorySlot(Inventory &inv)
	{
		{
			std::stringstream ss;
			if (inv.GetSelectedSlot() == id)
			{
				ss << "[" << id+1 << "]";
			}
			else
			{
				ss << " " << id+1 << " ";
			}
			num_text.SetText(ss.str());
		}

		name_text.SetText(GetNameForEntity(inv.slots[id]));

		count = inv.slots_count[id];
		std::stringstream ss;
		ss << "x " << count;
		count_text.SetText(ss.str());
	}

	void Render() const
	{
		num_text.Render(renderer, xoffset, yoffset);
		if (count)
		{
			name_text.Render(renderer, xoffset + 40, yoffset);
			count_text.Render(renderer, xoffset + 200, yoffset);
		}
	}

};

class HUD
{
private:
	GameApp &game;
	sdl::Renderer &renderer;

public:
	HUD(sdl::Renderer &renderer, GameApp *gameref)
	: game(*gameref), renderer(renderer)
	{
		SetHUD(this);

		text_worldname.box = true;
		text_worldname.box_bottom_offset = -10;
		text_worldname.shadow = 2;

		text_fps.box = true;

		text_help1.box = true;
		text_help2.box = true;
		text_help1.shadow = 1;
		text_help2.shadow = 1;

		text_inv_coins.shadow = 1;
		text_inv_health.shadow = 1;
		text_inv_hunger.shadow = 1;

		inv_slots.reserve(5);
		for (int i=0; i<5; i++)
		{
			inv_slots.emplace_back(renderer, font1, i);
		}

	}

	~HUD() { SetHUD(nullptr); }

	bool debug = false;

private:
	Font world_font { FindFile("RobotoSlab-Bold.ttf"), 32 };

	Font font1 { FindFile("DroidSans.ttf"), 16 };
	Font font2 { FindFile("DroidSans.ttf"), 11 };

	Text text_worldname { renderer, world_font, "..." };
	Text text_help1 { renderer, font2, "" };
	Text text_help2 { renderer, font2, "" };
	Text text_fps { renderer, font2, "" };

	Text text_inv_coins { renderer, font2, "" };
	Text text_inv_health { renderer, font2, "" };
	Text text_inv_hunger { renderer, font2, "" };

	std::vector<InventorySlot> inv_slots;

public:
	void UpdateHUD(float dt);

	void SetInventory(Player &player);

	void SetFPS(int fps);

	void SetWorldName();

	void RenderHUD(const Camera &cam) const;

	void RenderDebug(const Camera &cam) const;

	void Debug_Clear() const; //not really const

	void Debug_Rectangle(int x, int y, int w, int h);
	void Debug_Circle(int x, int y, int radius);

	Font & GetFont1() { return font1; }
	Font & GetFont2() { return font2; }
private:
	mutable float debug_delay = 0.0f;
	mutable std::vector<SDL_Rect> debug_rects;
	mutable std::vector<SDL_Rect> debug_circles;

};



#endif //HUD_H

