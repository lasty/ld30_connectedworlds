
#include "entity_renderer.h"

#include "sdl/headers.h"
#include "sdl/renderer.h"
#include "sdl/texture.h"
#include "sprite.h"

#include "gamedefs.h"
#include "world.h"
#include "player.h"
#include "entity.h"
#include "camera.h"

#include "shop.h"

#include "utils.h"

#include <glm/vec2.hpp>


void EntityRenderer::RenderEntities(const World & world, const Camera &cam) const
{
	//culling
	World::EntityListConst list = world.GetEntitiesInRange(cam.GetTopLeft(), cam.GetSize());

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

	SetTintColour(sprite.GetTexture(), e.tint_colour);
	sprite.Render(worldpos.x, worldpos.y, e.heading);

	if (e.DrawCircle())
	{
		SDL_SetRenderDrawColor(renderer.GetRenderer(), 0x22, 0xee, 0xee, 0xaa);
		RenderRadius(e, cam);
	}


	//if it is a shop, or the portal
	const ThingsWithInventory * shop = dynamic_cast<const ThingsWithInventory*>(&e);
	if (shop)
	{

		//render the stuff inside
		if (shop->inventory)
		{
			for(auto &e : shop->inventory->items)
			{
				if (e) RenderEntity(*e, cam);
			}
		}

		//Render text
		shop->Render(cam);
	}

}

#include <glm/glm.hpp>
#include <iostream>

void EntityRenderer::RenderEntity(const Player &p, const Camera &cam) const
{
	glm::vec2 worldpos = p.GetWorldPos();
	worldpos -= cam.GetOffset();

	//this is good enough for now.. needs more tweaking though

	float legs_time = p.walk_timer_legs;
	float arm_time = p.walk_timer_arms;

	float lsine = fabs(glm::sin(legs_time));
	float asine = fabs(glm::sin(arm_time));

	lsine = glm::clamp(lsine, 0.0f, 1.0f);
	asine = glm::clamp(asine, 0.0f, 1.0f);

	int index_arms = glm::mix<float>(0, arms_max, asine);
	int index_legs = glm::mix<float>(0, legs_max, lsine);

	//std::cout << "index_arms = " << index_arms << std::endl;

	if (index_arms < 0 or index_arms > arms_max) { std::cout << "index_arms out of range: " << index_arms << std::endl; }
	if (index_legs < 0 or index_legs > legs_max) { std::cout << "index_legs out of range: " << index_legs << std::endl; }

	index_arms = glm::clamp(index_arms, 0, arms_max);
	index_legs = glm::clamp(index_legs, 0, legs_max);

	auto & arms = player_arms.at(index_arms);

	auto & legs = player_legs.at(index_legs);



	SetTintColour(legs.GetTexture(), p.tint_colour);
	legs.Render(worldpos.x, worldpos.y, p.heading);

	SetTintColour(arms.GetTexture(), colour::white);
	arms.Render(worldpos.x, worldpos.y, p.heading);


	//SetTintColour(legs.GetTexture(), p.tint_colour);
	player_head.Render(worldpos.x, worldpos.y, p.heading);
	//SetTintColour(arms.GetTexture(), colour::white);
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
	const float radius = entity.radius;
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
			return player_head;

		case ent::coin:
		case ent::coin_silver:
			return coin_cents;

		case ent::coin_gold:
			return coin_dollar;

		case ent::food:
		case ent::food1:
			return food_ration;
		case ent::food2:
			return food_potatosalad;
		case ent::food3:
			return food_ham;

		case ent::none:
			return none_sprite;
		default:
			return none_sprite;
	}
}

