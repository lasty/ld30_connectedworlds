
#include "utils.h"

#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>

#include <glm/gtx/random.hpp>

#include "hud.h"

namespace {

std::vector<std::string> the_path_list;

};

std::vector<std::string> & GetPathList()
{
	return the_path_list;
}

void AddPath(const std::string &path)
{
	GetPathList().push_back(path);
}


//// try to locate a file by prepending all values in search path
std::string FindFile(const std::string &filename)
{
	for(auto &path : GetPathList())
	{
		std::string fullfilename = path + "/" + filename;
		try
		{
			std::ifstream in(fullfilename);

			if(in) return fullfilename;
		}
		catch (std::exception &e)
		{

		}
	}
	throw std::runtime_error("Could not find file '"+filename+"'");
}


////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
void seed_random() { srand(time(nullptr)); }

float random_float(float min, float max){ return glm::linearRand(min, max); }
float random_int(int min, int max) { return (glm::linearRand<float>(min, max+1)); }

float random_rotation() { return random_float(0.0f, 360.0f); }

float random_velocity() { return random_float(0.0f, 10.0f); }
float random_rot_velocity() { return random_float(-20.0f, 20.0f); }


HUD *debug_hud = nullptr;

void SetHUD(HUD *debughud)
{
	debug_hud = debughud;
}


void Debug_Rectangle(int x1, int y1, int w, int h)
{
	if (debug_hud) { debug_hud -> Debug_Rectangle(x1, y1, w, h); }
}

void Debug_Circle(int x, int y, int radius)
{
	if (debug_hud) { debug_hud -> Debug_Circle(x, y, radius); }
}


////////////////////////////////////////////////////////////////////////////////

// Some colours taken from  http://xkcd.com/color/rgb/  (Internet survey)

std::vector<glm::ivec4> colourmap =
	{ glm::ivec4{ 0xff, 0xff, 0xff, 0xff} //white

	, glm::ivec4{ 0xaa, 0xaa, 0xaa, 0xff} //grey

	, glm::ivec4{ 0xc5, 0xc9, 0xc7, 0xff} //silver

	, glm::ivec4{ 0xb6, 0x63, 0x25, 0xff} //copper

	//Too many golds to choose from...
	//, glm::ivec4{ 0xfa, 0xc2, 0x05, 0xff} //goldenrod
	//, glm::ivec4{ 0xdb, 0xb4, 0x0c, 0xff} //gold
	//, glm::ivec4{ 0xfc, 0xc0, 0x06, 0xff} //marigold
	, glm::ivec4{ 0xfd, 0xdc, 0x5c, 0xff} //light gold
	//, glm::ivec4{ 0xfd, 0xde, 0x6c, 0xff} // pale gold
	//, glm::ivec4{ 0xb5, 0x94, 0x10, 0xff} //dark gold

	, glm::ivec4{ 0x3b, 0x5b, 0x92 , 0xff} // denim blue

	, glm::ivec4{ 0x98, 0x00, 0x02, 0xff} // blood red

	};

/*  //template for inserting new ones


, glm::ivec4{
, 0xff} //

*/

const glm::ivec4 & GetColour(colour col)
{
	return colourmap.at((int)col);
}

void SetTintColour(sdl::Texture &texture, colour tint)
{
	const glm::ivec4 &col = GetColour(tint);

	SDL_SetTextureColorMod(texture.GetTexture(), col.r, col.g, col.b);
	SDL_SetTextureAlphaMod(texture.GetTexture(), col.a);
}

void SetDrawColour(sdl::Renderer &renderer, colour tint)
{
	const glm::ivec4 &col = GetColour(tint);

	SDL_SetRenderDrawColor(renderer.GetRenderer(), col.r, col.g, col.b, col.a);
}


