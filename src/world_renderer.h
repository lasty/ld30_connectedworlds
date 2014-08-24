#ifndef WORLD_RENDERER_H
#define WORLD_RENDERER_H

#include "sdl/renderer.h"
#include "sdl/texture.h"
#include "tile.h"

#include "camera.h"

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

	Tile grass1 { renderer, sprite_texture, { 0, 0, 64, 64} };
	Tile grass2 { renderer, sprite_texture, { 64, 0, 64, 64} };
	Tile grass3 { renderer, sprite_texture, { 128, 0, 64, 64} };
	Tile grass4 { renderer, sprite_texture, { 192, 0, 64, 64} };

	Tile cave1 { renderer, sprite_texture, { 0, 64, 64, 64} };
	Tile cave2 { renderer, sprite_texture, { 64, 64, 64, 64} };
	Tile cave3 { renderer, sprite_texture, { 128, 64, 64, 64} };
	Tile cave4 { renderer, sprite_texture, { 192, 64, 64, 64} };
	Tile cave5 { renderer, sprite_texture, { 192, 128, 64, 64} };
	Tile cave6 { renderer, sprite_texture, { 128, 128, 64, 64} };

	Tile stone1 { renderer, sprite_texture, { 0, 128, 64, 64} };
	Tile stone2 { renderer, sprite_texture, { 64, 128, 64, 64} };

	Tile none_tile { renderer, sprite_texture, { 0, 0, 0, 0} };


public:
	void RenderMap(const World & world, const Camera &cam) const
	{
		glm::vec2 offset = cam.GetOffset();
		glm::vec2 tl = cam.GetTopLeft();
		glm::vec2 br = cam.GetBottomRight();

		tl /= 64.0f;
		br /= 64.0f;

		// adjust slightly, or else we get blanks
		tl -= 1.0f;
		//br -= 0.5f;

		for (int x=tl.x; x<br.x; x++)
		{
			for (int y=tl.y; y<br.y; y++)
			{
				const MapTile & mt = world.GetXY(x,y);

				glm::vec2 worldpos = world.GetWorldPos(x, y);

				worldpos -= offset;

				const Tile &tile = GetTileRender(mt);

				tile.Render(worldpos.x, worldpos.y);
			}
		}
	}


	const Tile & GetTileRender(const MapTile &mt) const
	{
		switch (mt.tiledef)
		{
			case tile::grass1: return grass1;
			case tile::grass2: return grass2;
			case tile::grass3: return grass3;
			case tile::grass4: return grass4;
			case tile::cave1: return cave1;
			case tile::cave2: return cave2;
			case tile::cave3: return cave3;
			case tile::cave4: return cave4;
			case tile::cave5: return cave5;
			case tile::cave6: return cave6;
			case tile::rock1: return stone1;
			case tile::rock2: return stone2;

			default:
				return none_tile;
		}
	}

};



#endif // WORLD_RENDERER_H
