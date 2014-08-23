#ifndef GENERATORS_H
#define GENERATORS_H

#include "maptile.h"
#include "entity.h"

#include <vector>


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
		tg.Add(tile::dirt, 90);
		tg.Add(tile::grass, 10);
	}

	MapTile operator()(int x, int y) override
	{
		tile t = tg.Get();

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
		tg.Add(tile::stone, 90);
		tg.Add(tile::dirt, 50);
		tg.Add(tile::ore, 10);
	}


	MapTile operator()(int x, int y) override
	{
		tile t = tg.Get();

		MapTile m{t, 0};
		return m;
	}

	std::string GetName() const override { return "UnderWorld"; }
};


#endif // GENERATORS_H
