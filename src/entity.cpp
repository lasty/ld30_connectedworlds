
#include "entity.h"

#include "world.h"

#include "utils.h"

#include <glm/geometric.hpp>



void Entity::Update(float dt)
{
	if (world)
	{
		auto old_position = position;
		position += velocity * dt;
		if (HasCollision(*world))
		{
			position = old_position;
			velocity*= -0.2;
		}
	}
	else
	{
		position += velocity * dt;
	}

	heading += delta_heading * dt;

	if (ttl > 0.0f)
	{
		ttl -= dt;
		if (ttl <= 0.0f)
		{
			Kill();
		}
	}

	if (apply_friction and friction >= 0.0f)
	{
		if (glm::length(velocity) > 0.0f)
		{
			glm::vec2 fricvec = glm::normalize(velocity) * friction * dt;

			velocity -= fricvec;

			if (glm::length(velocity) < 0.01f)
			{
				velocity = {0.0f, 0.0f};
			}
		}
	}
}


void Entity::Kill()
{
	alive = false;
}


// Simple circle collision detection,  If distance between is less than the
// two particle's radius, then they collide
bool Entity::HasCollision(const Entity &other) const
{
	float dist = glm::distance(position, other.position);
	dist -= radius;
	dist -= other.radius;

	return dist <= 0.0f;
}



bool Entity::HasCollision(const World &world) const
{
	float minx = (position.x - (2*radius));
	float maxx = (position.x + (2*radius));
	float miny = (position.y - (2*radius));
	float maxy = (position.y + (2*radius));

	minx /= 64.0f;
	miny /= 64.0f;
	maxx /= 64.0f;
	maxy /= 64.0f;

	minx = round(minx-0.5f);
	miny = round(miny-0.5f);
	maxx = round(maxx);
	maxy = round(maxy);

	Debug_Rectangle(int(minx)*64, int(miny)*64, int(maxx-minx+1)*64, int(maxy-miny+1)*64);

	//int tests=0;

	for(int x = minx; x <= maxx; x++)
	{
		for(int y = miny; y <= maxy; y++)
		{
			//std::cout << "Testing point ("<<x<<", "<<y<<")\n";
			if (world.HasTileCollision(x, y) == false) continue;

			glm::vec2 tl = world.GetWorldPos(x, y);
			//const glm::vec2 br = world.GetWorldPos(x+1, y+1);

			//adjust by 1 pixel
			//br.x -= 1;
			//br.y -= 1;

			//tests++;

			bool coll = HasCollision(tl.x, tl.y, 64, 64);
			if (coll)
			{
				return true;
			}
		}
	}

	//std::cout << "collision tests: " << tests << std::endl;

	return false;
}


bool Entity::HasCollision(float x, float y, float width, float height) const
{
	// found from
	// http://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection

	//Debug_Circle(position.x, position.y, radius);
	Debug_Rectangle(x+1, y+1, width-1, height-1);

	const float closestX = glm::clamp(position.x, x, x+width);
	const float closestY = glm::clamp(position.y, y, y+height);

	const float distanceX = position.x - closestX;
	const float distanceY = position.y - closestY;

	const float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
	const float radiusSquared = radius * radius;

	return distanceSquared < radiusSquared;
}


