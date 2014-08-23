#ifndef MAPTILE_H
#define MAPTILE_H

class MapTile
{
public:
	tile tiledef = tile::none;
	int data = 0;
	//bool can_collide = false;

	MapTile() { }
	MapTile(const tile &t, int d=0) : tiledef(t), data(d) { }

};

#endif // MAPTILE_H
