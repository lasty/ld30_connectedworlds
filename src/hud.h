#ifndef HUD_H
#define HUD_H

#include "sdl/headers.h"
#include "sdl/renderer.h"
#include "font/font.h"
#include "font/text.h"

#include "utils.h"

#include <sstream>
#include <vector>

class GameApp;


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

		text_particle_count.shadow = 1;
		text_count.shadow = 1;
	}

	~HUD() { SetHUD(nullptr); }

	bool debug = true;

private:
	Font world_font { FindFile("RobotoSlab-Bold.ttf"), 32 };

	Font font1 { FindFile("DroidSans.ttf"), 16 };
	Font font2 { FindFile("DroidSans.ttf"), 11 };

	Text text_worldname { renderer, world_font, "..." };
	Text text_count { renderer, font2, "" };
	Text text_particle_count { renderer, font2, "" };
	Text text_fps { renderer, font2, "" };

public:
	void UpdateHUD(float dt);

	void SetFPS(int fps);

	void SetWorldName();

	void RenderHUD() const;

	void RenderDebug() const;

	void Debug_Clear();

	void Debug_Rectangle(int x, int y, int w, int h);
	void Debug_Circle(int x, int y, int radius);

private:
	std::vector<SDL_Rect> debug_rects;
	std::vector<SDL_Rect> debug_circles;

};



#endif //HUD_H

