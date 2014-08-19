
#include <iostream>

#include "sdl/app.h"

#include "sdl/headers.h"

#include "font/font.h"
#include "font/text.h"

#include "sdl/surface.h"
#include "sdl/texture.h"
#include "sdl/sound.h"
#include "sdl/mixer.h"

#include <glm/glm.hpp>

#include <sstream>
#include <vector>
#include <algorithm>

#define DATA_PATH "../data/"



class Tile
{
public:
	Tile(sdl::Renderer &renderer, sdl::Texture &texref, SDL_Rect coords)
	: rend(renderer)
	, tex(texref)
	, coords(coords)
	{ }
protected:
	sdl::Renderer &rend;
	sdl::Texture &tex;
	SDL_Rect coords;


public:
	void Render(int x, int y) const
	{
		const SDL_Rect position{x, y, coords.w, coords.h};
		rend.Copy(tex, &coords, &position);
	}
};

class Sprite : private Tile
{
public:
	Sprite(sdl::Renderer &renderer, sdl::Texture &texref, SDL_Rect coords, SDL_Point midpoint)
	: Tile(renderer, texref, coords)
	, midpoint(midpoint)
	{ }

protected:
	SDL_Point midpoint;

public:
	void Render(int x, int y, float angle) const
	{
		const SDL_Rect position{x, y, coords.w, coords.h};
		rend.CopyEx(tex, &coords, &position, angle, &midpoint);
	}
};


class Particle
{
public:
	Particle(Sprite & sprite, float x, float y, float angle)
	: sprite(&sprite)
	, position(x, y)
	, velocity(0.0f, 0.0f)
	, angle(angle)
	{ }

public:
	bool alive = true;
	Sprite *sprite = nullptr;
	glm::vec2 position;
	glm::vec2 velocity;
	float angle;
	float angle_velocity;
	float friction = 0.8f;
	float ttl=0.0f;

public:
	void Render() const
	{
		sprite->Render((int)position.x, (int)position.y, angle);
	}

	void Update(float dt)
	{
		position += velocity * dt;
		angle += angle_velocity * dt;

		if (ttl > 0.0f)
		{
			ttl -= dt;
			if (ttl <= 0.0f) alive = false;
		}

	}
};


const int windowwidth = 800;
const int windowheight = 600;
const int mapwidth = windowwidth/64 + 1;
const int mapheight = windowheight/64 + 1;

class TestApp : public sdl::App
{

public:

	Font font1 { DATA_PATH "DroidSans.ttf", 16 };
	Text text1 { renderer, font1, "Hello World" };
	Text text_count { renderer, font1, "Particle Count: " };

	sdl::Texture sprite_texture { renderer, DATA_PATH "sprites.png" };

	Tile brick { renderer, sprite_texture, { 0, 0, 64, 64} };
	Tile ground { renderer, sprite_texture, { 64, 0, 64, 64} };

	Sprite arrow { renderer, sprite_texture, { 0, 64, 64, 64}, { 64+32, 32} };
	Sprite circle { renderer, sprite_texture, { 64, 64, 64, 64}, { 64+32, 64+32} };

	sdl::Mixer mixer;
	sdl::Sound sound1 { DATA_PATH "powerup.wav" };

	std::vector<bool> map;
	void SetMap(int x, int y, bool value) { map.at((mapwidth * y) + x) = value; }
	bool GetMap(int x, int y) const { return map.at((mapwidth*y)+x); }


	std::vector<Particle> particles;


	TestApp()
	: App("Warmup 30", windowwidth, windowheight)
	{
		map.insert(map.begin(), (mapwidth*mapheight), false);

		NewMap();

		for(int i=0; i<10; i++)
		{
			NewParticle();
		}
	}

	void NewMap()
	{
		for (int x=0; x<mapwidth; x++)
		{
			for (int y=0; y<mapheight; y++)
			{
				int v = rand() % 2;
				v = false;
				if (y==0 or x==0 or x == mapwidth or y==mapheight) v = true;
				SetMap(x,y, (bool)(v));
			}
		}
	}


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

	void NewParticle()
	{
		int v = rand() % 2;
		auto &s = v ? arrow : circle;

		float x = rand() % windowwidth;
		float y = rand() % windowheight;
		float a = rand() % 360;

		Particle p { s, x, y, a };

		float vx = (rand() % 100) / 10.0f;
		float vy = (rand() % 100) / 10.0f;
		float vrot = (rand() % 100) / 10.0f;

		p.velocity = { vx, vy };
		p.angle_velocity = vrot;
		p.ttl = (rand() % 100) / 10.0f;

		particles.push_back(std::move(p));
	}

	void RenderParticles() const
	{
		for(auto &p : particles)
		{
			p.Render();
		}
	}

	void UpdateParticles(float dt)
	{
		for(auto &p : particles)
		{
			p.Update(dt);
		}

		const auto stillalive = [](Particle &p) { return not p.alive; };

		auto partition = std::remove_if(particles.begin(), particles.end(), stillalive);
		particles.erase(partition, particles.end());
	}


	void OnFPS(int fps) override
	{
		std::ostringstream ss;
		ss << "FPS: " << fps;

		SetTitle(ss.str());

		//text1.SetText(renderer, font1, ss.str());
	}

	void UpdateHUD(float dt)
	{
		std::ostringstream pc;
		pc << "Particle Count: " << particles.size();
		text_count.SetText(renderer, font1, pc.str());
	}

	void Render() const override
	{
		renderer.SetColour(20, 30, 40, 255);
		renderer.Clear();

		//renderer.Copy(sprite_texture, nullptr, nullptr);

		RenderMap();

		RenderParticles();

		text1.Render(renderer, 5, 5);

		text_count.Render(renderer, 5, -5);
	}

	void Update(float dt)
	{
		UpdateParticles(dt);

		UpdateHUD(dt);
	}

	void OnKey(SDL_KeyboardEvent &e, bool down) override
	{
		if (down)
		{
			if (e.keysym.sym == SDLK_ESCAPE)
			{
				Quit();
			}
			else if (e.keysym.sym == SDLK_SPACE)
			{
				mixer.PlaySound(sound1);
				for(int i=0; i<10; i++){ NewParticle(); }
			}
		}
	}
};


int main()
{

	TestApp app;

	app.Run();

}
