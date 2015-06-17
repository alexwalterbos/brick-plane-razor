#include "obstacle.h"

Obstacle::Obstacle(Material m, Rect r)
{
	material = m;
	rect = r;
}

Material Obstacle::getMaterial()
{
	return material;
}

Rect Obstacle::getRect()
{
	return rect;
}

