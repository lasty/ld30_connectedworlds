#ifndef GAME_H
#define GAME_H




#include "sdl/app.h"
#include "sdl/mixer.h"
#include "sdl/sound.h"

#include "particle.h"
#include "sprite.h"
#include "font/font.h"
#include "font/text.h"

#include "utils.h"

#include "world.h"

#include "gamedefs.h"

#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>

#include <algorithm>
#include <sstream>

// Hard coded values, because it's easier that way :/

const int windowwidth = 800;
const int windowheight = 600;
const int mapwidth = windowwidth/64 + 1;
const int mapheight = windowheight/64 + 1;



#include "hud.h"
#include "world_renderer.h"
#include "entity_renderer.h"
#include "sound_manager.h"


// Main game app class.

class GameApp : public sdl::App
{

public:
	HUD hud { renderer, this };

	WorldRenderer world_renderer { renderer };
	EntityRenderer entity_renderer { renderer };

	SoundManager sounds { mixer };

	World overworld { 1 };
	World underworld { 0 };

	int whichworld = 1;  //1 = overworld, 0 = underworld
	World & GetWorld() {  return whichworld==0? underworld : overworld; }
	const World & GetWorld() const {  return whichworld==0? underworld : overworld; }

	void SwitchWorlds()
	{
		whichworld = whichworld==0? 1: 0;
		hud.SetWorldName();
	 }

	int coins_score = 0; //Player's Score

	Player player {overworld};


	GameApp()
	: App("LD 30 - Connected Worlds", windowwidth, windowheight)
	{
		//initialize the map with enough items
		//map.insert(map.begin(), (mapwidth*mapheight), false);

		NewMap();

		//NewCoin(10);
	}

	//ground everywhere except borders are brick walls
	void NewMap()
	{
/*
		for (int x=0; x<mapwidth; x++)
		{
			for (int y=0; y<mapheight; y++)
			{
				//int v = rand() % 2;
				int v = false;
				if (y==0 or x==0 or x == (mapwidth-1) or y == (mapheight-1)) v = true;
				SetMap(x,y, (bool)(v));
			}
		}
*/
		hud.SetWorldName();
	}

	//draw the map on screen
	void RenderMap() const
	{
		const World & world = GetWorld();

		world_renderer.RenderMap(world);
	}


	void RenderEntities() const
	{
		const World & world = GetWorld();

		entity_renderer.RenderEntities(world);
	}



	//Create numcoins coins at random position on the map
	void NewCoin(int numcoins = 1)
	{
		GetWorld().AddCoins(numcoins);
	}

	//Render all particles, coins, player
	void RenderObjects() const
	{
		RenderEntities();

		entity_renderer.RenderPlayer(player);
	}


	void UpdatePlayer(float dt)
	{
		player.Update(dt);

/*
		if (player.HasCollision(GetWorld()))
		{
			std::cout << "Colliding in world" << std::endl;
			player.velocity.x *= -1.0f;
			player.velocity.y *= -1.0f;
		}
*/

		/*
		//Simple border testing
		float minx = 64.0f - player.radius;;
		float miny = 64.0f - player.radius;;
		if (player.position.x <= minx) { player.position.x = minx;  player.velocity.x *= -1.0f; }
		if (player.position.y <= miny) { player.position.y = miny;  player.velocity.y *= -1.0f; }

		float maxx = ((mapwidth-2)*64.0f) + player.radius;
		float maxy = ((mapheight-2)*64.0f) + player.radius;
		if (player.position.x >= maxx) { player.position.x = maxx;  player.velocity.x *= -1.0f; }
		if (player.position.y >= maxy) { player.position.y = maxy;  player.velocity.y *= -1.0f; }
		*/

	}


	//Update all particles, coins, player
	void UpdateObjects(float dt)
	{
		UpdatePlayer(dt);

		overworld.UpdateObjects(dt);
		underworld.UpdateObjects(dt);
	}


	//Gets called once per second with the number of frames
	void OnFPS(int fps) override
	{
		hud.SetFPS(fps);
	}



	// Gets called once per frame, to render the window.
	// Marked as const function so you can't change any state. (Do that in Upate)
	void Render() const override
	{
		//renderer.SetColour(0, 0, 0, 255);
		//renderer.Clear();

		//All these subfunctions must also be const functions.

		RenderMap();

		RenderObjects();

		hud.RenderHUD();
	}


	// Gets called once per frame with the time since last frame in seconds
	void Update(float dt)
	{
		hud.Debug_Clear();

		UpdateObjects(dt);

		hud.UpdateHUD(dt);
	}


	// Keyboard events get sent here
	void OnKey(SDL_KeyboardEvent &e, bool keydown) override
	{
		if (keydown)
		{
			if (e.keysym.sym == SDLK_ESCAPE)
			{
				Quit();
			}
			else if (e.keysym.sym == SDLK_SPACE)
			{
				sounds.Powerup();
				NewCoin(10);
			}
			else if (e.keysym.sym == SDLK_TAB)
			{
				SwitchWorlds();
			}
		}

		auto k = e.keysym.sym;

		if (k == SDLK_a or k == SDLK_LEFT) {  player.turning_left = keydown; }
		if (k == SDLK_d or k == SDLK_RIGHT) {  player.turning_right = keydown; }
		if (k == SDLK_w or k == SDLK_UP) {  player.thrusting = keydown; }
	}
};


#endif // GAME_H
