
#include "hud.h"

#include "game.h"

#include "font/font.h"
#include "font/text.h"

#include "camera.h"
#include "player.h"

#include "sdl/headers.h"

#include <iomanip>

void HUD::UpdateHUD(float dt)
{
	debug_delay -= dt;

	SetInventory(game.GetPlayer());

	std::ostringstream pc;
	pc << "Arrows/WASD: Move.  Tab: Switch worlds.  Space: More coins.  ESC: Quit.  ";
	//pc << "Particles: " << (particles.size() + coins.size() + 1);
	text_particle_count.SetText(pc.str());
}

void HUD::SetInventory(Player &player)
{
	std::ostringstream cc;
	int coins = player.GetCash();

	int dollars = coins / 100;
	int cents = coins % 100;
	cc << "Coins: $" << dollars <<".";
	cc << std::setw(2) << std::setfill('0');  cc<<cents;
	text_inv_coins.SetText(cc.str());

	std::ostringstream health;
	health << "Health: " << player.GetHealthPercent() << "%";
	text_inv_health.SetText(health.str());

	std::ostringstream hunger;
	hunger << "Hunger: " << player.GetHungerPercent() << "%";
	text_inv_hunger.SetText(hunger.str());
}

void HUD::SetFPS(int fps)
{
	std::ostringstream ss;
	ss << "FPS: " << fps;

	text_fps.SetText(ss.str());
	//SetTitle(ss.str());
}


void HUD::SetWorldName()
{
	std::string name = game.GetWorld().GetName();
	text_worldname.SetText(name);
}


void HUD::RenderHUD(const Camera &cam) const
{
	if (debug) { RenderDebug(cam); }

	int centerx = renderer.GetWidth() / 2;
	int textw = text_worldname.GetWidth() / 2;
	text_worldname.Render(renderer, centerx-textw, 10);

	//inventory/health/hunger
	text_inv_coins.Render(renderer, 5, -1);
	text_inv_hunger.Render(renderer, 5, -16);
	text_inv_health.Render(renderer, 5, -32);


	text_particle_count.Render(renderer, -10, -1);

	text_fps.Render(renderer, -5, 5);
}


void HUD::Debug_Clear() const
{
	//to make sure some events stay on the screen for at least a little time
	if (debug_delay <= 0.0f)
	{
		debug_delay = 0.05f;
		debug_rects.clear();
		debug_circles.clear();
	}
}

void HUD::Debug_Rectangle(int x, int y, int w, int h)
{
	if (not debug) return;
	//std::cout << "Rectangle ("<<x<< ", "<<y<<", "<<w<<", "<<h<<")" << std::endl;
	SDL_Rect r{x, y, w, h};
	debug_rects.push_back(r);
}


void HUD::Debug_Circle(int x, int y, int radius)
{
	if (not debug) return;
	SDL_Rect r{x, y, radius, 0};
	debug_circles.push_back(r);
}


void RenderCircle(const sdl::Renderer &renderer, int x, int y, int radius)
{
	const int steps = 32;
	glm::vec2 worldpos = {x, y};

	for (int i=0; i<steps; i++)
	{
		float rangle = (float(i) / float(steps)) * ( 2 * 3.1415);
		float x = glm::cos(rangle) * radius;
		float y = glm::sin(rangle) * radius;
		//SDL_RenderDrawLine(renderer.GetRenderer(), worldpos.x, worldpos.y, x+worldpos.x, y+worldpos.y);
		SDL_RenderDrawPoint(renderer.GetRenderer(), x+worldpos.x, y+worldpos.y);
	}
}



void HUD::RenderDebug(const Camera &cam) const
{
	if (not debug) return;

	SDL_SetRenderDrawColor(renderer.GetRenderer(), 0x22, 0xee, 0xbb, 0xff);

	glm::vec2 offset = cam.GetOffset();

	for(auto rect : debug_rects)
	{
		rect.x -= offset.x;
		rect.y -= offset.y;

		SDL_RenderDrawRect(renderer.GetRenderer(), &rect);
		//std::cout << "Rect ("<<rect.x<< ", "<<rect.y<<" : "<<rect.w<<", "<<rect.h<<")" << std::endl;
	}

	for(auto circ : debug_circles)
	{
		circ.x -= offset.x;
		circ.y -= offset.y;

		RenderCircle(renderer, circ.x, circ.y, circ.w);
	}
}

