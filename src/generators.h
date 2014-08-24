#ifndef GENERATORS_H
#define GENERATORS_H

#include "maptile.h"
#include "entity.h"

#include <vector>

#include <glm/gtc/noise.hpp>

//base map generator class
class Generator
{
public:
	virtual MapTile operator()(int x, int y) = 0;
	virtual std::string GetName() const = 0;
};


//pick a random tile based on a weighted list of chances
class TileGen
{
protected:
	struct chance_item
	{
		tile t;
		int chance;
	};

	int maxchance = 0;
	std::vector<chance_item> list;

public:
	void Add(tile t, int weight)
	{
		list.push_back({t, weight});
		maxchance += weight;
	}

	tile Get() const
	{
		int r = random_int(0, maxchance-1);

		tile t = tile::none;

		int sofar = 0;
		for(auto &i : list)
		{
			sofar += i.chance;
			if (sofar > r)
			{
				t = i.t;
				break;
			}
		}

		return t;
	}
};



class OverworldGenerator : public Generator
{
public:

	TileGen tg;

	OverworldGenerator()
	{
		tg.Add(tile::grass1, 90);
		tg.Add(tile::grass2, 40);
		tg.Add(tile::grass3, 20);
		tg.Add(tile::grass4, 10);
	}

	MapTile operator()(int x, int y) override
	{
		tile t = tg.Get();

		if (abs(x)<3 and abs(y)<3) t = tile::grass1;

		MapTile m{t, 0};
		return m;
	}

	std::string GetName() const override { return "OverWorld"; }
};


class UnderworldGenerator : public Generator
{
public:
	TileGen tg;

	UnderworldGenerator()
	{
		tg.Add(tile::rock1, 20);

		tg.Add(tile::cave1, 90);
		tg.Add(tile::cave2, 60);
		tg.Add(tile::cave3, 50);
		tg.Add(tile::cave4, 50);
		tg.Add(tile::cave5, 20);
		tg.Add(tile::cave6, 20);

		tg.Add(tile::rock2, 20);
	}


	MapTile operator()(int x, int y) override
	{
		glm::vec2 xy1 { x, y };
		glm::vec2 xy2 { x/100.0f, y/100.0f };

		tile t = tg.Get();


		if (abs(x)<3 and abs(y)<3) t = tile::cave1;

		MapTile m{t, 0};
		return m;
	}

	std::string GetName() const override { return "UnderWorld"; }
};


#endif // GENERATORS_H
