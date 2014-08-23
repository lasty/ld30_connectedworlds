
#include "hud.h"

#include "game.h"

#include "font/font.h"
#include "font/text.h"

#include "sdl/headers.h"

void HUD::UpdateHUD(float dt)
{
	//if (debug) { Debug_Clear(); }

	std::ostringstream cc;
	cc << "Coins: " << game.coins_score;;
	text_count.SetText(renderer, font1, cc.str());

	std::ostringstream pc;
	pc << "Arrows/WASD: Move.  Space: More coins.  ESC: Quit.  ";
	//pc << "Particles: " << (particles.size() + coins.size() + 1);
	text_particle_count.SetText(renderer, font2, pc.str());
}


void HUD::SetFPS(int fps)
{
	std::ostringstream ss;
	ss << "FPS: " << fps;

	text_fps.SetText(renderer, font2, ss.str());
	//SetTitle(ss.str());
}


void HUD::SetWorldName()
{
	std::string name = game.GetWorld().GetName();
	text_worldname.SetText(renderer, font1, name);
}


void HUD::RenderHUD() const
{
	if (debug) { RenderDebug(); }

	text_worldname.Render(renderer, 5, 5);

	text_count.Render(renderer, 5, -1);
	text_particle_count.Render(renderer, -10, -1);

	text_fps.Render(renderer, -5, 5);
}


void HUD::Debug_Clear()
{
	debug_rects.clear();
	debug_circles.clear();
}

void HUD::Debug_Rectangle(int x, int y, int w, int h)
{
	//std::cout << "Rectangle ("<<x<< ", "<<y<<", "<<w<<", "<<h<<")" << std::endl;
	SDL_Rect r{x, y, w, h};
	debug_rects.push_back(r);
}


void HUD::Debug_Circle(int x, int y, int radius)
{
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



void HUD::RenderDebug() const
{
	for(auto rect : debug_rects)
	{
		SDL_RenderDrawRect(renderer.GetRenderer(), &rect);
		//std::cout << "Rect ("<<rect.x<< ", "<<rect.y<<" : "<<rect.w<<", "<<rect.h<<")" << std::endl;
	}

	for(auto circ : debug_circles)
	{
		RenderCircle(renderer, circ.x, circ.y, circ.w);
	}
}

