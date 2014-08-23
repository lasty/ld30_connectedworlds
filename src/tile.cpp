
#include "tile.h"


#include "sdl/renderer.h"
#include "sdl/texture.h"
#include "sdl/headers.h"


Tile::Tile(sdl::Renderer &renderer, sdl::Texture &texref, SDL_Rect coords)
: rend(renderer)
, tex(texref)
, coords(coords)
{ }

void Tile::Render(int x, int y) const
{
	const SDL_Rect position{x, y, coords.w, coords.h};
	rend.Copy(tex, &coords, &position);
}


