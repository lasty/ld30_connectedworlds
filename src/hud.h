#ifndef HUD_H
#define HUD_H

#include "sdl/renderer.h"
#include "font/font.h"
#include "font/text.h"

#include "utils.h"

#include <sstream>

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
	}

private:
	Font font1 { FindFile("DroidSans.ttf"), 16 };
	Font font2 { FindFile("DroidSans.ttf"), 11 };

	Text text_worldname { renderer, font1, "..." };
	Text text_count { renderer, font2, "" };
	Text text_particle_count { renderer, font2, "" };
	Text text_fps { renderer, font2, "" };

public:
	void UpdateHUD(float dt);

	void SetFPS(int fps);

	void SetWorldName();

	void RenderHUD() const;
};



#endif //HUD_H

