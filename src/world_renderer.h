#ifndef WORLD_RENDERER_H
#define WORLD_RENDERER_H

#include "sdl/renderer.h"
#include "sdl/texture.h"
#include "tile.h"

#include "gamedefs.h"


#include <glm/vec2.hpp>


class WorldRenderer
{
private:
	sdl::Renderer & renderer;

public:
	WorldRenderer(sdl::Renderer &renderref) : renderer(renderref) { }

private:
	sdl::Texture sprite_texture { renderer, FindFile("terrain.png") };

	Tile grass { renderer, sprite_texture, { 0, 0, 64, 64} };
	Tile dirt { renderer, sprite_texture, { 64, 0, 64, 64} };
	Tile stone { renderer, sprite_texture, { 0, 64, 64, 64} };
	Tile ore { renderer, sprite_texture, { 64, 64, 64, 64} };

	Tile none_tile { renderer, sprite_texture, { 0, 0, 0, 0} };


public:
	void RenderMap(const World & world) const
	{
		for (int x=0; x<mapwidth; x++)
		{
			for (int y=0; y<mapheight; y++)
			{
				const MapTile & mt = world.GetXY(x,y);

				glm::vec2 worldpos = world.GetWorldPos(x, y);

				const Tile &tile = GetTileRender(mt);

				tile.Render(worldpos.x, worldpos.y);
			}
		}
	}


	const Tile & GetTileRender(const MapTile &mt) const
	{
		switch (mt.tiledef)
		{
			case tile::grass: return grass;
			case tile::dirt: return dirt;
			case tile::stone: return stone;
			case tile::ore: return ore;

			default:
				return none_tile;
		}
	}

};



#endif // WORLD_RENDERER_H
