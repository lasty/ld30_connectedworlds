
#include "sdl/app.h"
#include "sdl/mixer.h"
#include "sdl/sound.h"

#include "particle.h"
#include "sprite.h"
#include "font/font.h"
#include "font/text.h"

#include "utils.h"


#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>

#include <algorithm>
#include <sstream>

// Hard coded values, because it's easier that way :/

const int windowwidth = 800;
const int windowheight = 600;
const int mapwidth = windowwidth/64 + 1;
const int mapheight = windowheight/64 + 1;


float random_map_width() { return (random_float(0.0f, mapwidth-3) + 1) * 64.0f; }
float random_map_height() { return (random_float(0.0f, mapheight-3) + 1) * 64.0f; }

// Some more specific game entities

class Coin : public Particle
{
public:
	Coin(Sprite &sprite)
	: Particle(sprite, random_map_width(), random_map_height(), random_rotation())
	{
		angle_velocity = random_rot_velocity();
		radius = 20.0f;
	}
};


// Class to control the player with

class Player : public Particle
{
public:
	Player(Sprite &sprite)
	: Particle(sprite, random_map_width(), random_map_height(), random_rotation())
	{
		radius = 16.0f;
		friction = 0.9f;
	}

	bool turning_left = false;
	bool turning_right = false;
	bool thrusting = false;


	void Update(float dt)
	{
		const float turnrate = 200.0f;
		const float thrustrate = 800.0f;
		if (turning_left) angle -= dt * turnrate;
		if (turning_right) angle += dt * turnrate;
		if (thrusting)
		{
			float rangle = glm::radians(angle - 90.0f);  //90 degrees off, sprite points up

			// convert angle to vec2
			glm::vec2 thrustvec { glm::cos(rangle) , glm::sin(rangle) };

			thrustvec = glm::normalize(thrustvec) * thrustrate * dt;
			velocity += thrustvec;
		}

		Particle::Update(dt);
	}

};



// Main game app class.

class GameApp : public sdl::App
{

public:

	Font font1 { FindFile("DroidSans.ttf"), 16 };
	Font font2 { FindFile("DroidSans.ttf"), 11 };

	Text text1 { renderer, font1, "Get the coins..." };
	Text text_count { renderer, font2, "" };
	Text text_particle_count { renderer, font2, "" };
	Text text_fps { renderer, font2, "" };

	sdl::Texture sprite_texture { renderer, FindFile("sprites.png") };

	Tile brick { renderer, sprite_texture, { 0, 0, 64, 64} };
	Tile ground { renderer, sprite_texture, { 64, 0, 64, 64} };

	Sprite arrow { renderer, sprite_texture, { 0, 64, 64, 64}, { 32, 32} };
	Sprite circle { renderer, sprite_texture, { 64, 64, 64, 64}, { 32, 32} };

	sdl::Sound sound1 { FindFile("powerup.wav") };
	sdl::Sound sound2 { FindFile("beep.wav") };

	//2d tilemap in a 1d vector.  Just using bool for ground/wall
	std::vector<bool> map;
	void SetMap(int x, int y, bool value) { map.at((mapwidth * y) + x) = value; }
	bool GetMap(int x, int y) const { return map.at((mapwidth*y)+x); }

	//Not used anymore.. maybe I will add smoke or something
	std::vector<Particle> particles;

	//List of coins on the field
	std::vector<Coin> coins;

	int coins_score = 0; //Player's Score

	Player player{ arrow };

	GameApp()
	: App("LD 30 - Connected Worlds", windowwidth, windowheight)
	{
		//initialize the map with enough items
		map.insert(map.begin(), (mapwidth*mapheight), false);

		NewMap();

		NewCoin(10);
	}

	//ground everywhere except borders are brick walls
	void NewMap()
	{
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
	}


	//draw the map on screen
	void RenderMap() const
	{
		for (int x=0; x<mapwidth; x++)
		{
			for (int y=0; y<mapheight; y++)
			{
				bool v = GetMap(x,y);
				auto &t = v ? brick : ground;
				t.Render(x*64, y*64);
			}
		}
	}

	//Not used anymore
	void NewParticle()
	{
		//particles.push_back(std::move(p));
	}

	//Create numcoins coins at random position on the map
	void NewCoin(int numcoins = 1)
	{
		for(int i=0; i<numcoins; i++)
		{
			Coin c { circle };
			coins.push_back(c);
		}
	}

	//Render all particles, coins, player
	void RenderObjects() const
	{
		for(auto &p : particles)
		{
			p.Render();
		}
		for(auto &c : coins)
		{
			c.Render();
		}

		player.Render();
	}


	void UpdatePlayer(float dt)
	{
		player.Update(dt);

		//Simple border testing
		float minx = 64.0f - player.radius;;
		float miny = 64.0f - player.radius;;
		if (player.position.x <= minx) { player.position.x = minx;  player.velocity.x *= -1.0f; }
		if (player.position.y <= miny) { player.position.y = miny;  player.velocity.y *= -1.0f; }

		float maxx = ((mapwidth-2)*64.0f) + player.radius;
		float maxy = ((mapheight-2)*64.0f) + player.radius;
		if (player.position.x >= maxx) { player.position.x = maxx;  player.velocity.x *= -1.0f; }
		if (player.position.y >= maxy) { player.position.y = maxy;  player.velocity.y *= -1.0f; }

	}

	//Update all particles, coins, player
	void UpdateObjects(float dt)
	{
		UpdatePlayer(dt);

		for(auto &p : particles)
		{
			p.Update(dt);
		}

		//cannot add/change the vector while we are going through it, add more after
		int new_coins = 0;

		for(auto &c : coins)
		{
			c.Update(dt);
			if (player.HasCollision(c))
			{
				c.Kill();
				mixer.PlaySound(sound2);
				coins_score++;
				new_coins++;
			}
		}

		// lambda function to test whether we should remove this particle
		const auto not_alive = [](Particle &p) { return not p.alive; };

		// Remove any dead particles/coins...
		//
		// If you haven't seen this pattern before it can be confusing.
		// "remove_if" partitions the vector with a predicate function.
		// Anything returning true gets moved to the end.  It returns an
		// iterator marking the partition point.  Next we call erase to
		// actually remove the requested items (if any).
		//

		auto partition = std::remove_if(particles.begin(), particles.end(), not_alive);
		particles.erase(partition, particles.end());

		// Repeat for coins

		auto partition2 = std::remove_if(coins.begin(), coins.end(), not_alive);
		coins.erase(partition2, coins.end());

		// Add any new coins here.  We can't do this inside the loops above.
		NewCoin(new_coins);
	}


	//Gets called once per second with the number of frames
	void OnFPS(int fps) override
	{
		std::ostringstream ss;
		ss << "FPS: " << fps;

		//SetTitle(ss.str());

		text_fps.SetText(renderer, font2, ss.str());
	}


	void UpdateHUD(float dt)
	{
		std::ostringstream cc;
		cc << "Coins: " << coins_score;;
		text_count.SetText(renderer, font1, cc.str());

		std::ostringstream pc;
		pc << "Arrows/WASD: Move.  Space: More coins.  ESC: Quit.  ";
		pc << "Particles: " << (particles.size() + coins.size() + 1);
		text_particle_count.SetText(renderer, font2, pc.str());
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

		RenderHUD();
	}


	void RenderHUD() const
	{
		text1.Render(renderer, 5, 5);

		text_count.Render(renderer, 5, -1);
		text_particle_count.Render(renderer, -10, -1);

		text_fps.Render(renderer, -5, 5);
	}


	// Gets called once per frame with the time since last frame in seconds
	void Update(float dt)
	{
		UpdateObjects(dt);

		UpdateHUD(dt);
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
				mixer.PlaySound(sound1);
				NewCoin(10);
			}
		}

		auto k = e.keysym.sym;

		if (k == SDLK_a or k == SDLK_LEFT) {  player.turning_left = keydown; }
		if (k == SDLK_d or k == SDLK_RIGHT) {  player.turning_right = keydown; }
		if (k == SDLK_w or k == SDLK_UP) {  player.thrusting = keydown; }
	}
};

