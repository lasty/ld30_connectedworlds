#ifndef TILE_H
#define TILE_H

#include "sdl/renderer.h"
#include "sdl/texture.h"
#include "sdl/headers.h"


// Tiles class for background tilemap.  Does not rotate.

class Tile
{
public:
	Tile(sdl::Renderer &renderer, sdl::Texture &texref, SDL_Rect coords);

protected:
	sdl::Renderer &rend;
	sdl::Texture &tex;
	SDL_Rect coords;


public:
	void Render(int x, int y) const;
};


#endif // TILE_H

