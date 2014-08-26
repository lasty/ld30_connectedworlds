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
	InventorySlot(sdl::Renderer &rend, Font &font1, Font &font2, Font &font3, int slot_id)
	: renderer(rend), id(slot_id)
	, num_text(rend, font1, "1")
	, name_text(rend, font2, "Empty")
	, count_text(rend, font3, "x 0")
	{
		yoffset = (5-id) * -50;
		yoffset -= 40;
		xoffset = 10;

		num_text.shadow = true;
		name_text.shadow = true;
		count_text.shadow = true;

		num_text.box = true;
		//name_text.box = true;
		//count_text.box = true;
	}

	sdl::Renderer &renderer;
	//Font &font;
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
				ss << "[" << id+1 << "                 ]";
			}
			else
			{
				ss << " " << id+1;// << " ";
			}
			num_text.SetText(ss.str());
		}

		name_text.SetText(GetNameForEntity(inv.slots[id]));

		count = inv.slots_count[id];
		std::stringstream ss;
		ss << "x " << count;
		//ss << count << " x ";
		count_text.SetText(ss.str());
	}

	void Render() const
	{
		num_text.Render(renderer, xoffset, yoffset);
		if (count)
		{
			count_text.Render(renderer, xoffset + 30, yoffset - 2);
			name_text.Render(renderer, xoffset + 30, yoffset - 14);
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
		text_inv_health.box = true;
		text_inv_health.box_bottom_offset = 0;
		text_inv_hunger.shadow = 1;
		text_inv_hunger.box = true;

		inv_slots.reserve(5);
		for (int i=0; i<5; i++)
		{
			inv_slots.emplace_back(renderer, font1, tiny_font, tiny_font, i);
		}

	}

	~HUD() { SetHUD(nullptr); }

	bool debug = false;

private:
	Font world_font { FindFile("RobotoSlab-Bold.ttf"), 32 };

	Font font1 { FindFile("DroidSans.ttf"), 16 };
	Font font2 { FindFile("DroidSans.ttf"), 11 };

	Font bold_font { FindFile("RobotoSlab-Bold.ttf"), 24 };
	Font tiny_font { FindFile("DroidSans.ttf"), 9 };

	Text text_worldname { renderer, world_font, "..." };
	Text text_help1 { renderer, font2, "" };
	Text text_help2 { renderer, font2, "" };
	Text text_fps { renderer, font2, "" };

	Text text_inv_coins { renderer, font2, "" };
	Text text_inv_health { renderer, font1, "" };
	Text text_inv_hunger { renderer, font1, "" };

	std::vector<InventorySlot> inv_slots;

/*
	///XXX this just clutters up the screen.. need a better intro system

	std::vector<std::string> intro_text {
		"You control two players, stranded in the Overworld and Underworld"
		,"Press TAB to change worlds"
		,"The Overworld Has all the Shops to buy Food"
		,"The Underworld has all the Coins"
		,"Pass items to each other through the portal"
		,"You must work together to survive.  Good Luck"
	};

	Text intro_text_text { renderer, bold_font, "intro_text" };
	Text intro_text_text2 { renderer, tiny_font, "page" };
*/


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


	//int intro_page = -1;
	//bool IntroText(int i);


	Font & GetFont_small() { return tiny_font; }
	Font & GetFont_medium() { return font2; }
	Font & GetFont_large() { return font1; }
	Font & GetFont_big() { return bold_font; }

private:
	mutable float debug_delay = 0.0f;
	mutable std::vector<SDL_Rect> debug_rects;
	mutable std::vector<SDL_Rect> debug_circles;

};



#endif //HUD_H

