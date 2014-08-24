#ifndef ENTITY_RENDERER_H
#define ENTITY_RENDERER_H

#include "sdl/renderer.h"
#include "sdl/texture.h"
#include "sprite.h"

#include "utils.h"

#include <glm/vec2.hpp>

#include <vector>

class Player;
class World;
class Entity;
class Camera;

class EntityRenderer
{
private:
	sdl::Renderer & renderer;

public:
	EntityRenderer(sdl::Renderer &renderref) : renderer(renderref)
	{
		SetupCircle();
	}

private:

	sdl::Texture sprite_texture { renderer, FindFile("sprites.png") };

	Sprite arrow { renderer, sprite_texture, { 0, 64, 64, 64}, { 32 + 2, 32 + 4} };
	Sprite circle { renderer, sprite_texture, { 64, 64, 64, 64}, { 32, 32} };
	Sprite none_sprite { renderer, sprite_texture, { 0, 0, 0, 0}, { 0, 0} };


	sdl::Texture player_texture { renderer, FindFile("player.png") };

	Sprite player_head { renderer, player_texture, { 0, 0, 32, 32}, {16, 16} };

	std::vector<Sprite> player_arms {
	 { renderer, player_texture, { 0, 32, 32, 32}, {16, 16} }
	 , { renderer, player_texture, { 0, 64, 32, 32}, {16, 16} }
	 , { renderer, player_texture, { 0, 96, 32, 32}, {16, 16} }
	};

	int arms_max = player_arms.size() - 1;

	std::vector<Sprite> player_legs {
	{ renderer, player_texture, { 32, 32, 32, 32}, {16, 16} }
	, { renderer, player_texture, { 64, 32, 32, 32}, {16, 16} }
	, { renderer, player_texture, { 96, 32, 32, 32}, {16, 16} }

	, { renderer, player_texture, { 32, 64, 32, 32}, {16, 16} }
	, { renderer, player_texture, { 64, 64, 32, 32}, {16, 16} }
	, { renderer, player_texture, { 96, 64, 32, 32}, {16, 16} }
	};

	int legs_max = player_legs.size() - 1;

	std::vector<glm::vec2> circle_points;
	void SetupCircle();

public:
	void RenderEntities(const World & world, const Camera &cam) const;

	void RenderEntity(const Entity &e, const Camera &cam) const;

	void RenderEntity(const Player &p, const Camera &cam) const;

	void RenderRadius(const Entity &entity, const Camera &cam) const;

	const Sprite & GetSpriteForEntity(const Entity &e) const;
};



#endif // ENTITY_RENDERER_H

