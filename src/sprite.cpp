
#include "sprite.h"

#include "sdl/renderer.h"
#include "sdl/texture.h"
#include "sdl/headers.h"


Sprite::Sprite(sdl::Renderer &renderer, sdl::Texture &texref, SDL_Rect coords, SDL_Point midpoint)
: Tile(renderer, texref, coords)
, midpoint(midpoint)
{

}


void Sprite::Render(int x, int y, float angle) const
{
	const SDL_Rect position{x-midpoint.x, y-midpoint.y, coords.w, coords.h};
	rend.CopyEx(tex, &coords, &position, angle, &midpoint);
}

