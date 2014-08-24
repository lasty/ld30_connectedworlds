#ifndef WORLD_H
#define WORLD_H


#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>
#include <algorithm>

#include <glm/vec2.hpp>

#include "gamedefs.h"

#include "entity.h"
#include "items.h"
#include "player.h"


#include "maptile.h"

#include "generators.h"


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
public:
	World(Generator &gen)
	:gen(gen)
	{
		NewWorld();
	}

	void NewWorld()
	{
		ClearMap();

		ExpandTerrain(-20, -20, 20, 20, gen);
		//ExpandTerrain(0, 0, 5, 5, gen);
		world_name = gen.GetName();

		std::cout << "New world '" << world_name << "' mapsize is " << terrain.size() << std::endl;
	}


	std::string world_name = "undefined";

	std::map<MapPos, MapTile> terrain;

	std::vector<Entity> entities;

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

	void AddEntity(const Entity& e)
	{
		entities.push_back(e);
	}

	void AddCoins(int numcoins=1)
	{
		for(int i=0; i<numcoins; i++)
		{
			Coin e { random_map_width(), random_map_height(), random_rotation() };

			AddEntity(e);
		}
	}

	void UpdateObjects(float dt)
	{

		int new_coins = 0;
/*
		for(auto &c : coins)
		{
			c.Update(dt);
			if (player.HasCollision(c))
			{
				c.Kill();
				mixer.PlaySound(sound2);
				coins_score++;
				new_coins++;
			}
		}
*/

		// lambda function to test whether we should remove this particle
		//const auto not_alive = [](Particle &p) { return not p.alive; };

		// Remove any dead particles/coins...
		//
		// If you haven't seen this pattern before it can be confusing.
		// "remove_if" partitions the vector with a predicate function.
		// Anything returning true gets moved to the end.  It returns an
		// iterator marking the partition point.  Next we call erase to
		// actually remove the requested items (if any).
		//

/*
		auto partition = std::remove_if(particles.begin(), particles.end(), not_alive);
		particles.erase(partition, particles.end());
*/

		// Repeat for coins

/*
		auto partition2 = std::remove_if(coins.begin(), coins.end(), not_alive);
		coins.erase(partition2, coins.end());
*/

		// Add any new coins here.  We can't do this inside the loops above.
		AddCoins(new_coins);
	}


	std::vector<const Entity*> GetEntitiesInRange(const glm::vec2 &topleft, const glm::vec2 &size) const
	{
		std::vector<const Entity*> list;

		for(const Entity& e : entities)
		{
			if (e.HasCollision(topleft.x, topleft.y, size.x, size.y))
			{
				list.push_back(&e);
			}
		}

		return list;
	}

};


#endif // WORLD_H


