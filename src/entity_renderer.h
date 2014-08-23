#ifndef ENTITY_RENDERER_H
#define ENTITY_RENDERER_H

#include "sdl/renderer.h"
#include "sdl/texture.h"
#include "sprite.h"

#include "gamedefs.h"


#include <glm/vec2.hpp>


class EntityRenderer
{
private:
	sdl::Renderer & renderer;

public:
	EntityRenderer(sdl::Renderer &renderref) : renderer(renderref) { }

private:

	sdl::Texture sprite_texture { renderer, FindFile("sprites.png") };

	Sprite arrow { renderer, sprite_texture, { 0, 64, 64, 64}, { 32, 32} };
	Sprite circle { renderer, sprite_texture, { 64, 64, 64, 64}, { 32, 32} };
	Sprite none_sprite { renderer, sprite_texture, { 0, 0, 0, 0}, { 0, 0} };

public:
	void RenderEntities(const World & world) const
	{
		for(Entity const &e : world.entities)
		{
			//TODO culling

			glm::vec2 worldpos = e.GetWorldPos();

			const Sprite& sprite = GetSpriteForEntity(e);

			sprite.Render(worldpos.x, worldpos.y, e.heading);
		}

	}

	void RenderPlayer(const Player &player) const
	{
		arrow.Render(player.position.x, player.position.y, player.angle);
	}

	const Sprite & GetSpriteForEntity(const Entity &e) const
	{
		switch (e.entitydef)
		{
			case ent::player:
				return arrow;
			case ent::coin:
				return circle;
			case ent::none:
				return none_sprite;
			default:
				return none_sprite;
		}
	}
};



#endif // ENTITY_RENDERER_H

