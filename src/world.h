#ifndef WORLD_H
#define WORLD_H


#include "gamedefs.h"

#include "entity.h"
#include "items.h"
#include "player.h"
#include "maptile.h"
#include "generators.h"
#include "sound_manager.h"

#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <memory>

#include <glm/vec2.hpp>


struct MapPos
{
	int x;
	int y;

	bool operator<(const MapPos &rhs) const { return (x==rhs.x) ? (y<rhs.y) : (x<rhs.x); }
	bool operator==(const MapPos &rhs) const { return ((x==rhs.x) and (y==rhs.y)); }
};



class World
{
	Generator &gen;
	SoundManager &sounds;
public:
	World(Generator &gen, SoundManager &soundmanager)
	:gen(gen)
	,sounds(soundmanager)
	{
		NewWorld();
	}

	void NewWorld()
	{
		ClearMap();

		ExpandTerrain(-20, -20, 20, 20, gen);
		//ExpandTerrain(0, 0, 5, 5, gen);
		world_name = gen.GetName();

		AddCoins(50);
		AddFood(50);

		std::cout << "New world '" << world_name << "' mapsize is " << terrain.size() << std::endl;
	}


	std::string world_name = "undefined";

	std::map<MapPos, MapTile> terrain;

	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<Entity>> spawn_list;
	using EntityListConst = std::vector<const Entity*>;


	Player player { *this };

	Player & GetPlayer() { return player; }
	const Player & GetPlayer() const { return player; }

	void ClearMap()
	{
		terrain.clear();
		entities.clear();
	}


	bool HasXY(int x, int y) const
	{
		const MapPos xy{x,y};
		return terrain.find(xy) != terrain.end();
	}

	void SetXY(int x, int y, const MapTile &data)
	{
		const MapPos xy{x,y};

		terrain[xy] = data;
	}


	const MapTile & GetXY(int x, int y) const
	{
		const MapPos xy{x,y};
		auto it = terrain.find(xy);

		if (it != terrain.end())
		{
			return (it)->second;
		}
		else
		{
			return blank_tile;
		}
	}

	MapTile blank_tile {};


	bool HasTileCollision(int x, int y) const
	{
		const MapTile &m = GetXY(x,y);
		return CanCollide(m.tiledef);
	}


	void ExpandTerrain(int minx, int miny, int maxx, int maxy, Generator &gen)
	{
		for(int x=minx; x<=maxx; x++)
		{
			for(int y=miny; y<=maxy; y++)
			{
				if (not HasXY(x, y))
				{
					SetXY(x, y, gen(x, y));
				}
			}
		}
	}

	std::string GetName() const { return world_name; }

	glm::vec2 GetWorldPos(int x, int y) const
	{
		return glm::vec2{x*64.0f, y*64.0f};
	}

	float random_map_width() { return (random_float(-20.0f, 20.0f) ) * 64.0f; }
	float random_map_height() { return (random_float(-20.0f, 20.0f) ) * 64.0f; }


	void SpawnEntity(std::shared_ptr<Entity> e)
	{
		//TODO use std::move
		spawn_list.push_back(e);
	}

	void SpawnEntity(const std::string what, int x, int y, int data = 0)
	{
		if (what == "coin1")
		{
			SpawnEntity(std::make_shared<Coin_Cent>(x, y));
		}
		else if (what == "coin10")
		{
			SpawnEntity(std::make_shared<Coin_Silver>(x, y));
		}
		else if (what == "coin100")
		{
			SpawnEntity(std::make_shared<Coin_Gold>(x, y));
		}
		else if (what == "food1")
		{
			SpawnEntity(std::make_shared<Food_Ration>(x, y));
		}
		else if (what == "food2")
		{
			SpawnEntity(std::make_shared<Food_PotatoSalad>(x, y));

		}
		else if (what == "food3")
		{
			SpawnEntity(std::make_shared<Food_Roast>(x, y));
		}

		else
		{
			std::cout << "SpawnEntity:  Unknown Entity '" << what << "'" << std::endl;
		}
	}

	void AddCoins(int numcoins=1)
	{
		for(int i=0; i<numcoins; i++)
		{
			SpawnEntity("coin1", random_map_width(), random_map_height());
			SpawnEntity("coin10", random_map_width(), random_map_height());
			SpawnEntity("coin100", random_map_width(), random_map_height());
		}
	}

	void AddFood(int num=1)
	{
		for(int i=0; i<num; i++)
		{
			SpawnEntity("food1", random_map_width(), random_map_height());
			SpawnEntity("food2", random_map_width(), random_map_height());
			SpawnEntity("food3", random_map_width(), random_map_height());
		}
	}

	void UpdateObjects(float dt)
	{

		for(auto &e : entities)
		{
			e->Update(dt);

			if (player.HasCollision(*e))
			{

				if (player.CanPickup(e))
				{
					player.Pickup(std::move(e));
					sounds.Pickup();
				}
			}
		}


		// lambda function to test whether we should remove this (is the pointer empty, or is it not alive?
		const auto not_alive = [](std::shared_ptr<Entity> &e) { return not e or not e->StillAlive(); };

		// Remove any dead entities...
		//
		// If you haven't seen this pattern before it can be confusing.
		// "remove_if" partitions the vector with a predicate function.
		// Anything returning true gets moved to the end.  It returns an
		// iterator marking the partition point.  Next we call erase to
		// actually remove the requested items (if any).
		//

		auto partition = std::remove_if(entities.begin(), entities.end(), not_alive);
		entities.erase(partition, entities.end());


		// Add any new entities here.  We can't do this inside the loop above.

		for (auto &e : spawn_list)
		{
			entities.push_back(std::move(e));
		}
		spawn_list.clear();

	}


	EntityListConst GetEntitiesInRange(const glm::vec2 &topleft, const glm::vec2 &size) const
	{
		EntityListConst list;

		for(const auto& e : entities)
		{
			if (e->HasCollision(topleft.x, topleft.y, size.x, size.y))
			{
				list.push_back(e.get());
			}
		}

		return list;
	}

};


#endif // WORLD_H


