#ifndef ENTITY_RENDERER_H
#define ENTITY_RENDERER_H

#include "sdl/renderer.h"
#include "sdl/texture.h"
#include "sprite.h"

#include "utils.h"

class Player;
class World;
class Entity;


class EntityRenderer
{
private:
	sdl::Renderer & renderer;

public:
	EntityRenderer(sdl::Renderer &renderref) : renderer(renderref) { }

private:

	sdl::Texture sprite_texture { renderer, FindFile("sprites.png") };

	Sprite arrow { renderer, sprite_texture, { 0, 64, 64, 64}, { 32 + 2, 32 + 4} };
	Sprite circle { renderer, sprite_texture, { 64, 64, 64, 64}, { 32, 32} };
	Sprite none_sprite { renderer, sprite_texture, { 0, 0, 0, 0}, { 0, 0} };

public:
	void RenderEntities(const World & world) const;

	void RenderEntity(const Entity &e) const;
	void RenderPlayer(const Player &player) const;

	void RenderRadius(const Entity &entity) const;

	const Sprite & GetSpriteForEntity(const Entity &e) const;
};



#endif // ENTITY_RENDERER_H

