
#include "hud.h"

#include "game.h"

#include "font/font.h"
#include "font/text.h"


void HUD::UpdateHUD(float dt)
{
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

	text_worldname.Render(renderer, 5, 5);

	text_count.Render(renderer, 5, -1);
	text_particle_count.Render(renderer, -10, -1);

	text_fps.Render(renderer, -5, 5);
}


