#ifndef SPRITE_H
#define SPRITE_H

#include "tile.h"

#include "sdl/renderer.h"
#include "sdl/texture.h"
#include "sdl/headers.h"


// Sprite class, which rotates around a midpoint

class Sprite : public Tile
{
public:
	Sprite(sdl::Renderer &renderer, sdl::Texture &texref, SDL_Rect coords, SDL_Point midpoint);

protected:
	SDL_Point midpoint;

public:
	void Render(int x, int y, float angle) const;
};

#endif // SPRITE_H

