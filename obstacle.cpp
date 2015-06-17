#include "obstacle.h"

Obstacle::Obstacle(Material m, Rect r, bool b)
{
	material = m;
	rect = r;
	bottom = b;
}

Material Obstacle::getMaterial()
{
	return material;
}

Rect Obstacle::getRect()
{
	return rect;
}

bool Obstacle::isBottom()
{
	return bottom;
}
