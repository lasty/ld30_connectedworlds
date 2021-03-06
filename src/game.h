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

#include "shop.h"

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

#include "generators.h"

#include "camera.h"

// Main game app class.

class GameApp : public sdl::App
{

public:
	HUD hud { renderer, this };

	WorldRenderer world_renderer { renderer };
	EntityRenderer entity_renderer { renderer };

	SoundManager sounds { mixer };

	OverworldGenerator gen_over;
	UnderworldGenerator gen_under;

	World overworld { gen_over, sounds };
	World underworld { gen_under, sounds };

	std::shared_ptr<SharedInvArea> portal;

	std::shared_ptr<Shop> shop1;
	std::shared_ptr<Shop> shop2;
	std::shared_ptr<Shop> shop3;

	int whichworld = 1;  //1 = overworld, 0 = underworld
	World & GetWorld() {  return whichworld==0? underworld : overworld; }
	const World & GetWorld() const {  return whichworld==0? underworld : overworld; }

	Player & GetPlayer() { return GetWorld().GetPlayer(); }
	const Player & GetPlayer() const { return GetWorld().GetPlayer(); }

	void SwitchWorlds()
	{
		GetPlayer().LostFocus();
		whichworld = whichworld==0? 1: 0;
		hud.SetWorldName();
		GetCamera().SetTransition( { 0.0f, (whichworld-0.5f) * 1000.0f} );
		sounds.GoToWorld(whichworld);
	 }

	glm::vec2 cam_size { renderer.GetWidth(), renderer.GetHeight() };
	Camera cam_over { cam_size, overworld.GetPlayer().position };
	Camera cam_under { cam_size, overworld.GetPlayer().position };


	Camera & GetCamera() { return whichworld==0? cam_under : cam_over; }
	const Camera & GetCamera() const { return whichworld==0? cam_under : cam_over; }


	int coins_score = 0; //Player's Score

	//int intro_page = 0;

	GameApp()
	: App("LD 30 - Starving Symbiosis  (Connected Worlds)", windowwidth, windowheight)
	{
		//initialize the map with enough items
		//map.insert(map.begin(), (mapwidth*mapheight), false);

		//NewMap();

		//NewCoin(10);
		hud.SetWorldName();

		SpawnWorldEntities();
		InitShops();

		SetPlayerText(overworld.GetPlayer());
		SetPlayerText(underworld.GetPlayer());

		//hud.IntroText(intro_page);

		/// TODO refactor

		overworld.GetPlayer().BigMessage("Starving Symbiosis", 5.0f);
		overworld.GetPlayer().SetMessage("Press TAB to Change Worlds.  You can throw/drop items on the Portal and Shops)", 10.0f);

		underworld.GetPlayer().BigMessage("Starving Symbiosis", 5.0f);
		underworld.GetPlayer().SetMessage("Press TAB to Change Worlds.  You can throw/drop items on the Portal and Shops)", 10.0f);
	}


	//ground everywhere except borders are brick walls
	void NewMap()
	{
		overworld.NewWorld();
		underworld.NewWorld();

		SpawnWorldEntities();

		InitShops();
		hud.SetWorldName();
	}


	void SpawnWorldEntities()
	{
		overworld.AddCoins(10);
		//overworld.AddFood(100);
		underworld.AddCoins(100);
	}


	void SetShopText(ThingsWithInventory &shop)
	{
		shop.text_above.reset( new Text(renderer, hud.GetFont_large(), "toptext") );
		shop.text_below.reset( new Text(renderer, hud.GetFont_medium(), "bottext") );
		shop.text_above->box = true;
		shop.text_above->shadow = true;
		shop.text_below->box = true;
		shop.text_below->shadow = true;
	}


	void SetPlayerText(Player &player)
	{
		player.big_text.reset( new Text(renderer, hud.GetFont_big(), "") );
		player.msg_text.reset( new Text(renderer, hud.GetFont_medium(), "") );

		//player.big_text->box = true;
		player.big_text->shadow = true;
		player.msg_text->box = true;
		player.msg_text->shadow = true;
	}


	void InitShops()
	{
		portal.reset( new SharedInvArea(150.0f, 50.0f) );

		SetShopText(*portal);


		overworld.SpawnEntity(portal);
		underworld.SpawnEntity(portal);

		int shopy = -200;
		int shopx = -300;
		int shopspacing = 500;


		shop1.reset( new Shop(overworld, shopx + 0*shopspacing, shopy, "Ration", "food1", 100) );
		SetShopText(*shop1);
		overworld.SpawnEntity(shop1);

		shop2.reset( new Shop(overworld, shopx + 1*shopspacing, shopy, "Potato Salad", "food2", 500) );
		SetShopText(*shop2);
		overworld.SpawnEntity(shop2);

		shop3.reset( new Shop(overworld, shopx + 2*shopspacing, shopy, "Roast Ham", "food3", 1000) );
		SetShopText(*shop3);
		overworld.SpawnEntity(shop3);
	}

	//draw the map on screen
	void RenderMap() const
	{
		const World & world = GetWorld();

		world_renderer.RenderMap(world, GetCamera());
	}


	void RenderEntities() const
	{
	}



	//Create numcoins coins at random position on the map
	void NewCoin(int numcoins = 1)
	{
		GetWorld().AddCoins(numcoins);
	}

	//Render all particles, coins, player
	void RenderObjects() const
	{
		const World & world = GetWorld();

		entity_renderer.RenderEntities(world, GetCamera());

		const Player& player = GetPlayer();
		entity_renderer.RenderEntity(player, GetCamera());

		player.RenderText(GetCamera());
	}


	void UpdatePlayer(float dt)
	{
		GetPlayer().SetLookAt(world_mouse_pos.x, world_mouse_pos.y);

		overworld.GetPlayer().Update(dt);
		underworld.GetPlayer().Update(dt);
	}

	void UpdateCamera(float dt)
	{
		cam_over.Follow(overworld.GetPlayer());
		cam_under.Follow(underworld.GetPlayer());

		cam_over.Update(dt);
		cam_under.Update(dt);
	}

	//Update all particles, coins, player
	void UpdateObjects(float dt)
	{
		if (portal)
			portal->heading += (whichworld ? 180.0f : -180.0f) * dt;

		UpdatePlayer(dt);
		UpdateCamera(dt);

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
		renderer.SetColour(0, 0, 0x22, 255);
		renderer.Clear();

		//All these subfunctions must also be const functions.

		RenderMap();

		RenderObjects();

		hud.RenderHUD(GetCamera());

		//SDL_Delay(10);

		hud.Debug_Clear();

	}


	// Gets called once per frame with the time since last frame in seconds
	void Update(float dt) override
	{
		world_mouse_pos = ScreenToWorld(mouse_pos);

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
				//sounds.Pickup();
				//NewCoin(10);
				//GetWorld().AddFood(10);

				//bool nomoreintro = hud.IntroText(++intro_page);
				//if (nomoreintro)
				{
					GetPlayer().Throw();
				}

			}
			else if (e.keysym.sym == SDLK_TAB or e.keysym.sym == SDLK_RETURN)
			{
				SwitchWorlds();
			}
			else if (e.keysym.sym == SDLK_n)
			{
				NewMap();
			}

			else if (e.keysym.sym == SDLK_1)
			{
				sounds.Beep();
				GetPlayer().GetInventory().ChangeSlot(0);
			}
			else if (e.keysym.sym == SDLK_2)
			{
				sounds.Beep();
				GetPlayer().GetInventory().ChangeSlot(1);
			}
			else if (e.keysym.sym == SDLK_3)
			{
				sounds.Beep();
				GetPlayer().GetInventory().ChangeSlot(2);
			}
			else if (e.keysym.sym == SDLK_4)
			{
				sounds.Beep();
				GetPlayer().GetInventory().ChangeSlot(3);
			}
			else if (e.keysym.sym == SDLK_5)
			{
				sounds.Beep();
				GetPlayer().GetInventory().ChangeSlot(4);
			}

			else if (e.keysym.sym == SDLK_F1)
			{
				hud.debug = not hud.debug;
			}
		}

		auto k = e.keysym.sym;

		float dx = 0.0f;
		float dy = 0.0f;
		bool setx = false;
		bool sety = false;
		if (k == SDLK_a or k == SDLK_LEFT) {  setx = true; dx = keydown ? -1.0f : 0.0f; }
		if (k == SDLK_d or k == SDLK_RIGHT) {  setx = true; dx = keydown ? +1.0f : 0.0f; }
		if (k == SDLK_w or k == SDLK_UP) {  sety = true; dy = keydown ? -1.0f : 0.0f; }
		if (k == SDLK_s or k == SDLK_DOWN) {  sety = true; dy = keydown ? +1.0f : 0.0f; }

		if (setx and sety)
		{
			GetPlayer().SetMoveDirection(dx, dy);
		}
		else if (setx)
		{
			GetPlayer().SetMoveDirectionX(dx);
		}
		else if (sety)
		{
			GetPlayer().SetMoveDirectionY(dy);
		}
	}

	glm::vec2 mouse_pos;
	glm::vec2 world_mouse_pos;

	void OnMouseMove(int x, int y) override
	{
		mouse_pos.x = x;
		mouse_pos.y = y;

		world_mouse_pos = ScreenToWorld(mouse_pos);

		Debug_Circle(world_mouse_pos.x, world_mouse_pos.y, 20);
	}

	void OnMouseButton(int x, int y, int button, bool down) override
	{
		//std::cout << "button " << button << " down " << down << std::endl;

		mouse_pos.x = x;
		mouse_pos.y = y;

		world_mouse_pos = ScreenToWorld(mouse_pos);

		// TODO HUD culling

		if (down)
		{
			//bool nomoreintro = hud.IntroText(++intro_page);
			//if (nomoreintro)
			{

				if (button == 1)
				{
					GetPlayer().Use();
				}

				if (button == 3)
				{
					GetPlayer().Throw();
				}
			}

		}
	}

	glm::vec2 ScreenToWorld(glm::vec2 p) const
	{
		glm::vec2 r = p + GetCamera().GetOffset();

		return r;
	}

	glm::vec2 WorldToScreen(glm::vec2 p) const
	{
		glm::vec2 r = p - GetCamera().GetOffset();

		return r;
	}

};


#endif // GAME_H
