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

	std::vector<glm::vec2> circle_points;
	void SetupCircle();

public:
	void RenderEntities(const World & world, const Camera &cam) const;

	void RenderEntity(const Entity &e, const Camera &cam) const;

	void RenderRadius(const Entity &entity, const Camera &cam) const;

	const Sprite & GetSpriteForEntity(const Entity &e) const;
};



#endif // ENTITY_RENDERER_H

