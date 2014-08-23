#ifndef WORLD_H
#define WORLD_H


#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>
#include <algorithm>

#include <glm/vec2.hpp>

//#include "mapdata.h"

enum class ent
{
	none,
	player,
	coin
};

enum class tile
{
	none,
	ground,
	brick
};


class MapTile
{
public:
	tile tiledef = tile::none;
	int data = 0;

	MapTile() { }
	MapTile(const tile &t, int d=0) : tiledef(t), data(d) { }
};


class Entity
{
public:
	ent entitydef = ent::none;
	int data = 0;

	Entity() { }
	glm::vec2 position;
	float heading;

	const glm::vec2 & GetWorldPos() const { return position; }

};


class Generator
{
public:
	virtual MapTile operator()(int x, int y) = 0;
	virtual std::string GetName() const = 0;
};


class OverworldGenerator : public Generator
{
public:
	MapTile operator()(int x, int y) override
	{
		int r = random_int(0, 100);

		tile t = tile::ground;
		if (r > 90) t = tile::brick;

		MapTile m{t, 0};
		return m;
	}

	std::string GetName() const override { return "OverWorld"; }
};


class UnderworldGenerator : public Generator
{
public:
	MapTile operator()(int x, int y) override
	{
		int r = random_int(0, 100);

		tile t = tile::brick;
		if (r > 80) t = tile::ground;

		MapTile m{t, 0};
		return m;
	}

	std::string GetName() const override { return "UnderWorld"; }
};

struct MapPos
{
	int x;
	int y;

	bool operator<(const MapPos &rhs) const { return (x==rhs.x) ? (y<rhs.y) : (x<rhs.x); }
	bool operator==(const MapPos &rhs) const { return ((x==rhs.x) and (y==rhs.y)); }
};



class World
{
public:
	World(int which)
	{
		if (which == 1)
		{
			OverworldGenerator gen;
			NewWorld(gen);
		}
		else if (which == 0)
		{
			UnderworldGenerator gen;
			NewWorld(gen);
		}
		else throw std::logic_error("world number not defined");
	}


	void NewWorld(Generator &gen)
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


	void ExpandTerrain(int minx, int miny, int maxx, int maxy, Generator &gen)
	{
		std::cout << "\nGenerating Map: " << std::endl;
		for(int x=minx; x<=maxx; x++)
		{
			for(int y=miny; y<=maxy; y++)
			{
				std::cout << "x: " << x << " y:" << y << "  HasXY(): " << HasXY(x,y) << std::endl;
				if (not HasXY(x, y))
				{
					SetXY(x, y, gen(x, y));
				}
			}
		}
		std::cout << "\n" << std::endl;
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
			Entity e;
			e.position = glm::vec2{ random_map_width(), random_map_height()};
			e.heading = random_rotation();
			e.entitydef = ent::coin;

			AddEntity(e);
		}
	}
};


#endif // WORLD_H


