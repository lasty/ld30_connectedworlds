
#include "entity_renderer.h"

#include "sdl/headers.h"
#include "sdl/renderer.h"
#include "sdl/texture.h"
#include "sprite.h"

#include "gamedefs.h"
#include "world.h"
#include "player.h"

#include <glm/vec2.hpp>


void EntityRenderer::RenderEntities(const World & world) const
{
	for(Entity const &e : world.entities)
	{
		//TODO culling

		glm::vec2 worldpos = e.GetWorldPos();

		const Sprite& sprite = GetSpriteForEntity(e);

		sprite.Render(worldpos.x, worldpos.y, e.heading);
	}

}

void EntityRenderer::RenderEntity(const Entity &e) const
{
	glm::vec2 worldpos = e.GetWorldPos();

	const Sprite& sprite = GetSpriteForEntity(e);

	sprite.Render(worldpos.x, worldpos.y, e.heading);
}


void EntityRenderer::RenderPlayer(const Player &player) const
{
	RenderEntity(player);//arrow.Render(player.position.x, player.position.y, player.heading);
	//RenderRadius(player);
}


void EntityRenderer::RenderRadius(const Entity &entity) const
{
	const int steps = 16;
	const float radius = entity.radius;
	glm::vec2 worldpos = entity.GetWorldPos();

	for (int i=0; i<steps; i++)
	{
		float rangle = (float(i) / float(steps)) * ( 2 * 3.1415);
		float x = glm::cos(rangle) * radius;
		float y = glm::sin(rangle) * radius;
		//SDL_RenderDrawLine(renderer.GetRenderer(), worldpos.x, worldpos.y, x+worldpos.x, y+worldpos.y);
		SDL_RenderDrawPoint(renderer.GetRenderer(), x+worldpos.x, y+worldpos.y);
	}
}


const Sprite & EntityRenderer::GetSpriteForEntity(const Entity &e) const
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


