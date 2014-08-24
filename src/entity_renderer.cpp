
#include "entity_renderer.h"

#include "sdl/headers.h"
#include "sdl/renderer.h"
#include "sdl/texture.h"
#include "sprite.h"

#include "gamedefs.h"
#include "world.h"
#include "player.h"

#include "camera.h"

#include <glm/vec2.hpp>


void EntityRenderer::RenderEntities(const World & world, const Camera &cam) const
{
	//culling
	std::vector<const Entity*> list = world.GetEntitiesInRange(cam.GetTopLeft(), cam.GetSize());

	for(const Entity * e : list)
	{
		RenderEntity(*e, cam);
	}
}

void EntityRenderer::RenderEntity(const Entity &e, const Camera &cam) const
{
	glm::vec2 worldpos = e.GetWorldPos();
	worldpos -= cam.GetOffset();

	const Sprite& sprite = GetSpriteForEntity(e);

	sprite.Render(worldpos.x, worldpos.y, e.heading);

	if (e.DrawCircle())
	{
		SDL_SetRenderDrawColor(renderer.GetRenderer(), 0xee, 0xbb, 0x22, 0xaa);
		RenderRadius(e, cam);
	}
}


void EntityRenderer::SetupCircle()
{
	const int steps = 16;
	for (int i=0; i<steps; i++)
	{
		float rangle = (float(i) / float(steps)) * glm::radians(360.0f);
		float x = glm::cos(rangle);
		float y = glm::sin(rangle);
		glm::vec2 xy { x , y };
		circle_points.push_back(xy);
	}
}


void EntityRenderer::RenderRadius(const Entity &entity, const Camera &cam) const
{
	const float radius = entity.radius + 8;
	glm::vec2 worldpos = entity.GetWorldPos();
	worldpos -= cam.GetOffset();

	for (unsigned i=0; i<circle_points.size(); i++)
	{
		glm::vec2 p1 = circle_points[i];
		glm::vec2 p2 = circle_points.at( (i+1)%circle_points.size() );

		p1 = p1 * radius + worldpos;
		p2 = p2 * radius + worldpos;

		SDL_RenderDrawLine(renderer.GetRenderer(), p1.x, p1.y, p2.x, p2.y);
		//SDL_RenderDrawPoint(renderer.GetRenderer(), x+worldpos.x, y+worldpos.y);
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


